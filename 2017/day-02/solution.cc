#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <regex>
#include <string>
#include <vector>

namespace views = ranges::views;

std::vector<int> parse_digits(auto &line) {
    return line | views::tokenize(std::regex{"[0-9]+"}) |
           views::transform([](auto &chunk) { return std::stoi(chunk); }) | ranges::to<std::vector<int>>;
}

int difference(const std::vector<int> &cells) {
    auto min = ranges::min(cells);
    auto max = ranges::max(cells);
    return max - min;
}

int divisors(const std::vector<int> &cells) {
    for (auto [i, a] : views::enumerate(cells)) {
        for (auto [j, b] : views::enumerate(cells)) {
            if (i == j) {
                continue;
            }

            if (a % b == 0) {
                return a / b;
            }
        }
    }

    throw std::logic_error("no divisors present");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    std::vector<std::vector<int>> lines;

    {
        std::ifstream in{argv[1]};
        ranges::copy(
            ranges::getlines(in) | views::transform([](auto &line) { return parse_digits(line); }),
            ranges::back_inserter(lines));
    }

    fmt::print("part 1: {}\n", ranges::accumulate(views::transform(lines, difference), 0));
    fmt::print("part 2: {}\n", ranges::accumulate(views::transform(lines, divisors), 0));

    return 0;
}
