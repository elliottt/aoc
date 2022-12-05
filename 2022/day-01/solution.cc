#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    std::vector<int> totals;
    {
        std::ifstream in{argv[1]};
        totals =
            ranges::getlines(in) | views::split("") | views::transform([](auto &&rng) {
                return ranges::accumulate(rng | views::transform([](std::string &str) { return std::stoi(str); }), 0);
            }) |
            ranges::to<std::vector> | ranges::actions::sort(ranges::greater{});
    }

    fmt::print("part 1: {}\n", totals[0]);
    fmt::print("part 2: {}\n", ranges::accumulate(totals | views::take(3), 0));

    return 0;
}
