#include <cassert>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

int priority(char c) {
    if ('a' <= c && c <= 'z') {
        return c - 96;
    }
    return c - 38;
}

bool contains(std::string_view str, char c) {
    return str.find(c) != str.npos;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::vector<std::string> rucksacks;

    {
        std::ifstream in{argv[1]};
        rucksacks = ranges::getlines(in) | ranges::to<std::vector>;
    }

    fmt::print(
        "part 1: {}\n",
        ranges::accumulate(
            views::transform(
                rucksacks,
                [](auto &rucksack) {
                    auto middle = rucksack.length() / 2;
                    auto front = rucksack.substr(0, middle);
                    auto back = rucksack.substr(middle);
                    assert(front.length() == back.length());

                    auto c = ranges::find_if(front, [&back](auto c) { return contains(back, c); });
                    assert(c != front.end());

                    return priority(*c);
                }),
            0));

    fmt::print(
        "part 2: {}\n",
        ranges::accumulate(
            views::chunk(rucksacks, 3) | views::transform([](auto &&rng) {
                auto &front = ranges::front(rng);
                auto rest = views::tail(std::move(rng));
                auto c = ranges::find_if(front, [&rest](auto c) {
                    return ranges::all_of(rest, [c](auto &str) { return contains(str, c); });
                });
                assert(c != front.end());

                return priority(*c);
            }),
            0));

    return 0;
}
