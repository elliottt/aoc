#include <fmt/core.h>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

using std::ifstream, std::string, std::vector, std::regex;
using namespace ranges;

struct rule {
    int l1;
    int h1;
    int l2;
    int h2;

    static rule parse(const string &line) {
        auto l1 = stoi(line.substr(line.find(':') + 2));
        auto h1 = stoi(line.substr(line.find('-') + 1));
        auto l2 = stoi(line.substr(line.rfind(' ') + 1));
        auto h2 = stoi(line.substr(line.rfind('-') + 1));
        return {l1, h1, l2, h2};
    }

    bool valid(int value) const {
        return (l1 <= value && value <= h1) || (l2 <= value && value <= h2);
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    vector<rule> rules{};

    vector<int> me{};
    vector<vector<int>> others{};

    {
        ifstream in{argv[1]};

        for (auto [ix, lines] : getlines(in) | views::split("") | views::enumerate) {
            switch (ix) {
            case 0:
                for (auto const &line : lines) {
                    rules.emplace_back(rule::parse(line));
                }
                break;

            case 1:
                for (auto const &line : lines | views::drop(1)) {
                    for (auto &match : line | views::tokenize(regex{"[[:digit:]]+"})) {
                        me.emplace_back(stoi(match));
                    }
                }
                break;

            case 2:
                for (auto const &line : lines | views::drop(1)) {
                    auto &ticket = others.emplace_back();
                    for (auto &match : line | views::tokenize(regex{"[[:digit:]]+"})) {
                        ticket.emplace_back(stoi(match));
                    }
                }
            }
        }
    }

    auto invalid = ranges::accumulate(
        others | views::transform([&rules](auto const &ticket) {
            return ranges::accumulate(
                ticket | views::transform([&rules](auto n) {
                    if (ranges::any_of(rules, [n](auto const &rule) { return rule.valid(n); })) {
                        return 0;
                    } else {
                        return n;
                    }
                }),
                0);
        }),
        0);

    fmt::print("part 1: {}\n", invalid);

    return 0;
}
