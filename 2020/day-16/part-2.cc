#include <fmt/core.h>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

using namespace ranges;
using namespace std;

struct rule {
    string name;
    int l1;
    int h1;
    int l2;
    int h2;

    static rule parse(const string &line) {
        auto name = line.substr(0, line.find(':'));
        auto l1 = stoi(line.substr(line.find(':') + 2));
        auto h1 = stoi(line.substr(line.find('-') + 1));
        auto l2 = stoi(line.substr(line.rfind(' ') + 1));
        auto h2 = stoi(line.substr(line.rfind('-') + 1));
        return {name, l1, h1, l2, h2};
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

        for (auto [ix, lines] :
             getlines(in) | views::split("") | views::enumerate) {
            switch (ix) {
            case 0:
                for (auto const &line : lines) {
                    rules.emplace_back(rule::parse(line));
                }
                break;

            case 1:
                for (auto const &line : lines | views::drop(1)) {
                    for (auto &match :
                         line | views::tokenize(regex{"[[:digit:]]+"})) {
                        me.emplace_back(stoi(match));
                    }
                }
                break;

            case 2:
                for (auto const &line : lines | views::drop(1)) {
                    auto &ticket = others.emplace_back();
                    for (auto &match :
                         line | views::tokenize(regex{"[[:digit:]]+"})) {
                        ticket.emplace_back(stoi(match));
                    }
                }
            }
        }
    }

    auto valid = others | views::filter([&rules](auto const &ticket) {
                     return ranges::all_of(ticket, [&rules](auto n) {
                         return ranges::any_of(rules, [n](auto const &rule) {
                             return rule.valid(n);
                         });
                     });
                 }) |
                 to<vector>();

    // rule index to potential columns
    vector<vector<int>> constraints(rules.size(), vector<int>{});

    // collect constraints
    for (auto const &p : rules | views::enumerate) {
        auto ix = p.first;
        auto &rule = p.second;
        for (auto col : views::ints(0, static_cast<int>(constraints.size()))) {
            if (ranges::all_of(valid, [col, &rule](auto const &ticket) {
                            return rule.valid(ticket[col]);
                        })) {
                constraints[ix].emplace_back(col);
            }
        }
    }

    // experimentally, there are no guesses to make when solving the constraint set
    vector<int> solution(rules.size(), -1);
    while (true) {
        auto it = ranges::find_if(constraints, [](auto const &cs) { return cs.size() == 1; });
        if (it == constraints.end()) {
            break;
        }

        auto col = it->front();
        solution[std::distance(constraints.begin(), it)] = col;

        for (auto &cs : constraints) {
            cs.erase(ranges::remove(cs, col), cs.end());
        }
    }

    auto res = ranges::accumulate(
        rules | views::enumerate | views::transform([&solution, &me](auto const &p) {
            auto &[ix, rule] = p;
            if (rule.name.substr(0, 9) == "departure") {
                return static_cast<int64_t>(me[solution[ix]]);
            } else {
                return 1L;
            }
        }), 1L, ranges::multiplies{});

    fmt::print("part 2: {}\n", res);

    return 0;
}
