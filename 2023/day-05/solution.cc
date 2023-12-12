#include <charconv>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

#include "common/interval.h"

namespace views = ranges::views;

std::pair<int64_t, size_t> parse_int(std::string_view str) {
    int64_t n;
    auto [res, ec] = std::from_chars(str.begin(), str.end(), n);
    return {n, std::distance(str.begin(), res)};
}

using Range = aoc::Interval<int64_t>;

struct Mapping {
    Range range;
    int64_t diff;

    static Mapping parse(std::string_view str) {
        auto [dest, dest_len] = parse_int(str);
        auto [source, source_len] = parse_int(str.substr(dest_len + 1));
        auto [len, _] = parse_int(str.substr(dest_len + 1 + source_len + 1));
        return Mapping{Range{source, source + len}, dest - source};
    }

    Mapping(Range range, int64_t diff) : range{range}, diff{diff} {}
};

struct Map {
    std::string from;
    std::string to;
    std::vector<Mapping> mappings;

    Map() = default;

    static Map parse(auto &&rng) {}

    int64_t apply(int64_t val) const {
        for (auto [ix, mapping] : views::enumerate(this->mappings)) {
            if (mapping.range.contains(val)) {
                return val + mapping.diff;
            }
        }

        return val;
    }

    int64_t min(Range range) const {
        std::vector<int64_t> results;
        std::vector<Range> work{range};

        while (!work.empty()) {
            auto range = work.back();
            work.pop_back();

            bool matched = false;
            for (auto &map : this->mappings) {
                if (auto overlap = range.merge(map.range)) {
                    results.push_back(std::min(overlap.first() + map.diff, overlap.last() + map.diff));

                    auto [left, right] = range.subtract(map.range);
                    if (!left.empty()) {
                        work.push_back(left);
                    }
                    if (!right.empty()) {
                        work.push_back(right);
                    }

                    matched = true;
                    break;
                }
            }

            if (!matched) {
                results.emplace_back(range.first());
            }
        }

        return ranges::min(results);
    }

    /// Return the map that corresponds to apply this map, then other.
    Map and_then(const Map &other) const {
        Map result;
        auto add = [&result](auto range, auto diff) {
            // fmt::print("   > adding [{},{}) -> {}\n", range.min, range.max, diff);
            result.mappings.emplace_back(range, diff);
        };

        result.from = this->from;
        result.to = other.to;

        // The overlapping ranges that will need to be composed.
        auto work = this->mappings;

        auto queue = [&work](auto range, auto diff) { work.emplace_back(range, diff); };

        std::vector<bool> overlapped(other.mappings.size(), false);

        while (!work.empty()) {
            auto next = work.back();
            work.pop_back();

            bool queued = false;

            Range adjusted = next.range + next.diff;

            for (auto [ix, to] : views::enumerate(other.mappings)) {
                if (auto overlap = adjusted.merge(to.range)) {
                    overlapped[ix] = true;

                    add(overlap - next.diff, next.diff + to.diff);

                    auto [below, above] = adjusted.subtract(overlap);

                    if (!below.empty()) {
                        queue(below - next.diff, next.diff);
                    }

                    if (!above.empty()) {
                        queue(above - next.diff, next.diff);
                    }

                    queued = true;

                    break;
                }
            }

            // If no rule applied, pass the mapping through
            if (!queued) {
                add(next.range, next.diff);
            }
        }

        for (auto [ix, to] : views::enumerate(other.mappings)) {
            if (!overlapped[ix]) {
                add(to.range, to.diff);
            }
        }

        ranges::sort(result.mappings, ranges::less{}, [](auto &m) { return m.range.min; });

        return result;
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::vector<int64_t> seeds;
    std::vector<Map> mappings;

    {
        std::ifstream in{argv[1]};

        for (auto &&rng : ranges::getlines(in) | views::split("")) {
            auto &&line = *ranges::begin(rng);
            std::string_view str(&*ranges::begin(line), ranges::distance(line));

            if (line.starts_with("seeds:")) {
                seeds = views::drop(str, 7) | views::split(' ') | views::transform([](auto &&chunk) {
                            std::string_view str(&*chunk.begin(), ranges::distance(chunk));
                            return parse_int(str).first;
                        }) |
                        ranges::to<std::vector>;
                continue;
            }

            auto &mapping = mappings.emplace_back();
            auto end = str.find("-");
            mapping.from = std::string(str.substr(0, end));
            end += 4;
            mapping.to = std::string(str.substr(end, str.find(' ') - end));

            mapping.mappings = views::drop(rng, 1) | views::transform([](auto &&chunk) {
                                   std::string_view str(&*ranges::begin(chunk), ranges::distance(chunk));
                                   return Mapping::parse(str);
                               }) |
                               ranges::to<std::vector>;
        }
    }

    Map composed = mappings.front();
    for (auto &map : views::tail(mappings)) {
        composed = composed.and_then(map);
    }

    fmt::print("part 1: {}\n", ranges::min(views::transform(seeds, [&composed](auto seed) {
                   return composed.apply(seed);
               })));

    fmt::print("part 2: {}\n", ranges::min(views::chunk(seeds, 2) | views::transform([&composed](auto &&rng) {
                                               auto it = ranges::begin(rng);
                                               auto start = *it++;
                                               auto len = *it++;

                                               return composed.min(Range{start, start + len});
                                           })));

    return 0;
}
