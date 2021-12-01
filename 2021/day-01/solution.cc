#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    std::vector<int> depths;
    {
        std::ifstream in{argv[1]};
        ranges::copy(
            ranges::getlines(in) | views::transform([](auto &line) { return stoi(line); }),
            ranges::back_inserter(depths));
    }

    fmt::print("part 1: {}\n", ranges::count_if(views::zip(depths, views::tail(depths)), [](auto p) {
                   auto [a, b] = p;
                   return a < b;
               }));

    auto windows = views::zip_with(
        [](auto a, auto b, auto c) { return a + b + c; },
        depths,
        views::drop(depths, 1),
        views::drop(depths, 2));

    fmt::print("part 2: {}\n", ranges::count_if(views::zip(windows, views::tail(windows)), [](auto p) {
                   auto [a, b] = p;
                   return a < b;
               }));

    return 0;
}
