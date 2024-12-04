#include <charconv>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <regex>
#include <string>
#include <vector>

namespace views = ranges::views;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::string memory;
    {
        std::ifstream in{argv[1]};
        for (auto &line : ranges::getlines(in)) {
            memory.append(line);
        }
    }

    std::vector<std::pair<int, int>> muls;
    {
        std::regex regex{"mul\\(([0-9]{1,3}),([0-9]{1,3})\\)"};
        std::smatch match;
        auto start = memory.cbegin();
        while (std::regex_search(start, memory.cend(), match, regex)) {
            start = match[0].second;

            std::pair<int, int> mul;
            std::from_chars(match[1].first.base(), match[1].second.base(), mul.first);
            std::from_chars(match[2].first.base(), match[2].second.base(), mul.second);
            muls.push_back(mul);
        }
    }

    fmt::print(
        "part 1: {}\n",
        ranges::accumulate(muls | views::transform([](auto &p) { return p.first * p.second; }), 0));

    muls.clear();
    {
        std::regex regex{"don't\\(\\)|do\\(\\)|mul\\(([0-9]{1,3}),([0-9]{1,3})\\)"};
        std::smatch match;
        auto start = memory.cbegin();
        bool appending = true;
        while (std::regex_search(start, memory.cend(), match, regex)) {
            start = match[0].second;
            if (match[0].str() == "do()") {
                appending = true;
            } else if (match[0].str() == "don't()") {
                appending = false;
            } else if (appending) {
                std::pair<int, int> mul;
                std::from_chars(match[1].first.base(), match[1].second.base(), mul.first);
                std::from_chars(match[2].first.base(), match[2].second.base(), mul.second);
                muls.push_back(mul);
            }
        }
    }

    fmt::print(
        "part 2: {}\n",
        ranges::accumulate(muls | views::transform([](auto &p) { return p.first * p.second; }), 0));

    return 0;
}
