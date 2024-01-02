#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/math.h"

namespace views = ranges::views;

struct Rule;

using Rules = std::unordered_map<std::string, Rule>;

struct Rule {
    std::string left;
    std::string right;
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::string instrs;
    std::vector<std::string> keys;
    Rules rules;

    {
        std::ifstream in{argv[1]};

        std::getline(in, instrs);

        // skip the empty line
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        for (auto &line : ranges::getlines(in)) {
            Rule res;
            res.left = line.substr(7, 3);
            res.right = line.substr(12, 3);

            rules.insert({std::string(line.substr(0, 3)), res});
            keys.emplace_back(line.substr(0, 3));
        }
    }

    if (rules.contains("AAA")) {
        int steps = 0;
        std::string node = "AAA";
        for (auto c : instrs | views::cycle) {
            if (node == "ZZZ") {
                break;
            }

            if (c == 'L') {
                node = rules[node].left;
            } else {
                node = rules[node].right;
            }

            steps++;
        }

        fmt::print("part 1: {}\n", steps);
    }

    {
        std::vector<std::pair<std::string, uint64_t>> nodes;

        for (const auto &key : keys) {
            if (key[2] == 'A') {
                nodes.emplace_back(key, 0);
            }
        }

        for (auto &[start, steps] : nodes) {

            auto node = start;
            for (auto c : instrs | views::cycle) {
                steps++;

                if (c == 'L') {
                    node = rules[node].left;
                } else {
                    node = rules[node].right;
                }

                if (node[2] == 'Z') {
                    break;
                }
            }
        }

        fmt::print("part 2: {}\n", ranges::accumulate(nodes, 1UL, aoc::lcm<uint64_t>, [](auto &p) {
                       return p.second;
                   }));
    }

    return 0;
}
