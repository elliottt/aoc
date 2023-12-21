#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::vector<std::string> lines;

    {
        std::ifstream in{argv[1]};
        lines = ranges::getlines(in) | ranges::to<std::vector>;
    }

    {
        auto sorted = lines;
        for (auto &line : sorted) {
            ranges::sort(line);
        }

        std::vector<size_t> counts;

        struct Checksum {
            int twos{0};
            int threes{0};

            Checksum operator+(const Checksum &other) const {
                return {this->twos + other.twos, this->threes + other.threes};
            }
        };

        auto checksum = ranges::accumulate(
            views::transform(
                sorted,
                [&counts](auto &line) {
                    counts = views::chunk_by(line, ranges::equal_to{}) |
                             views::transform([](auto &&rng) { return ranges::size(rng); }) | ranges::to<std::vector>;

                    Checksum res;

                    if (ranges::contains(counts, 2)) {
                        res.twos = 1;
                    }

                    if (ranges::contains(counts, 3)) {
                        res.threes = 1;
                    }

                    return res;
                }),
            Checksum{});

        fmt::print("part 1: {}\n", checksum.twos * checksum.threes);
    }

    {
        for (auto [ix, line] : views::enumerate(lines)) {
            auto rng = views::drop(lines, ix+1);
            auto it = ranges::find_if(rng, [&line](auto &other) {
                return ranges::count(views::zip_with(ranges::equal_to{}, line, other), false) == 1;
            });

            if (it != ranges::end(rng)) {
                auto rng = views::zip_with(ranges::equal_to{}, line, *it);
                auto off = ranges::distance(ranges::begin(rng), ranges::find(rng, false));
                line.erase(off, 1);
                fmt::print("part 2: {}\n", line);
                break;
            }
        }
    }

    return 0;
}
