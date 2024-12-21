#include <charconv>
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

    std::vector<std::vector<int>> after;
    std::vector<std::vector<int>> correct;
    std::vector<std::vector<int>> incorrect;

    {

        std::ifstream in{argv[1]};
        auto to_int = [](auto chunk) -> int {
            auto *begin = &*chunk.begin();
            auto len = ranges::distance(chunk);
            int result;
            std::from_chars(begin, begin + len, result);
            return result;
        };

        for (auto line : ranges::getlines(in)) {
            if (line.empty()) {
                break;
            }

            auto rng = line | views::split('|') | views::transform(to_int);

            auto it = rng.begin();
            auto key = *it++;
            auto value = *it++;

            if (after.size() <= value) {
                after.resize(value + 1);
            }

            after[value].push_back(key);
        }

        for (auto line : ranges::getlines(in)) {
            auto update = line | views::split(',') | views::transform(to_int) | ranges::to<std::vector>;

            bool valid = true;
            for (auto [ix, page] : update | views::enumerate) {
                auto rest = update | views::drop(ix + 1);
                if (!ranges::all_of(rest, [page, &after](auto next) { return ranges::contains(after[next], page); })) {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                correct.emplace_back(std::move(update));
            } else {
                incorrect.emplace_back(std::move(update));
            }
        }
    }

    {
        int middles = 0;
        for (auto &update : correct) {
            auto middle = update.size() / 2;
            middles += update[middle];
        }

        fmt::print("part 1: {}\n", middles);
    }

    {
        int middles = 0;
        std::vector<int> replacement;
        for (auto &update : incorrect) {
            replacement = update;
            ranges::sort(replacement, ranges::greater{}, [&update, &after](auto page) {
                return ranges::accumulate(
                    update | views::transform(
                                 [page, &after](auto other) { return ranges::contains(after[other], page) ? 1 : 0; }),
                    0);
            });

            auto middle = replacement.size() / 2;
            middles += replacement[middle];
        }

        fmt::print("part 2: {}\n", middles);
    }

    return 0;
}
