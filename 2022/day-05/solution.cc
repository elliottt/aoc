#include <cassert>
#include <cctype>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

using Stacks = std::vector<std::string>;

struct Move {
    int amount;
    int from;
    int to;

    Move(int amount, int from, int to) : amount{amount}, from{from}, to{to} {}

    static Move parse(std::string &str) {
        auto amount = std::stoi(str.substr(5));
        auto from = std::stoi(str.substr(str.find("from ") + 5));
        auto to = std::stoi(str.substr(str.find("to ") + 3));
        return Move{amount, from, to};
    }

    void applyOne(Stacks &stacks) const {
        auto &from = stacks[this->from - 1];
        auto &to = stacks[this->to - 1];
        for (auto i = 0; i < this->amount; i++) {
            auto c = from.back();
            from.pop_back();
            to.push_back(c);
        }
    }

    void applyMany(Stacks &stacks) const {
        auto &from = stacks[this->from - 1];
        auto &to = stacks[this->to - 1];
        auto start = std::next(from.begin(), from.size() - this->amount);
        to.append(start, from.end());
        from.erase(start, from.end());
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    Stacks stacks;
    std::vector<Move> moves;

    {
        std::ifstream in{argv[1]};
        auto lines = ranges::getlines(in) | views::split("") |
                     views::transform([](auto &&rng) { return ranges::to<std::vector>(rng); }) |
                     ranges::to<std::vector>;

        assert(lines.size() == 2);

        stacks = std::vector<std::string>(lines[0].front().size());

        for (auto &line : lines[0]) {
            for (auto [c, col] : views::zip(line, stacks)) {
                if (std::isalpha(c)) {
                    col.push_back(c);
                }
            }
        }

        stacks.erase(ranges::remove(stacks, ""), stacks.end());

        for (auto &stack : stacks) {
            ranges::actions::reverse(stack);
        }

        moves = lines[1] | views::transform(&Move::parse) | ranges::to<std::vector>;
    }

    auto part_1_stacks = stacks;
    for (auto &move : moves) {
        move.applyOne(part_1_stacks);
    }

    fmt::print(
        "part 1: {}\n",
        fmt::join(part_1_stacks | views::transform([](auto &stack) { return stack.back(); }), ""));

    for (auto &move : moves) {
        move.applyMany(stacks);
    }

    fmt::print("part 2: {}\n", fmt::join(stacks | views::transform([](auto &stack) { return stack.back(); }), ""));

    return 0;
}
