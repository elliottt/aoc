#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

auto combinations(const std::vector<int> &sizes, int acc, int off) {
    if (acc == 150) {
        return 1;
    }

    // prune off impossible branches
    if (acc > 150 || off >= sizes.size()) {
        return 0;
    }

    return combinations(sizes, acc + sizes[off], off + 1) + combinations(sizes, acc, off + 1);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    std::vector<int> sizes{};
    {
        std::ifstream in{argv[1]};
        sizes =
            ranges::getlines(in) | views::transform([](auto &line) { return stoi(line); }) | ranges::to<std::vector>();
    }

    fmt::print("part 1: {}\n", combinations(sizes, 0, 0));

    return 0;
}
