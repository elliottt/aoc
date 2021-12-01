#include <fmt/core.h>
#include <fmt/format.h>
#include <fstream>
#include <map>
#include <range/v3/all.hpp>
#include <regex>
#include <string>
#include <vector>

using namespace ranges;
using namespace std;

using sue = map<string, int>;

sue parse_sue(const string &line) {
    sue res{};
    auto words = line | views::tokenize(regex{"[\\w]+"}) | to<vector<string>>();
    for (auto const &p : words | views::drop(2) | views::chunk(2)) {
        res[p[0]] = stoi(p[1]);
    }
    return res;
}

bool matches(const sue &target, const sue &candidate) {
    return ranges::all_of(candidate, [target](auto const &p) {
        // the key will always be present in the target, as it's fully defined
        auto it = target.find(p.first);

        if (p.first == "cats" || p.first == "trees") {
            return p.second > it->second;
        } else if (p.first == "pomeranians" || p.first == "goldfish") {
            return p.second < it->second;
        } else {
            return p.second == it->second;
        }
    });
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    sue target{
        {"children", 3},
        {"cats", 7},
        {"samoyeds", 2},
        {"pomeranians", 3},
        {"akitas", 0},
        {"vizslas", 0},
        {"goldfish", 5},
        {"trees", 3},
        {"cars", 2},
        {"perfumes", 1},
    };

    vector<sue> sues{};

    {
        ifstream in{argv[1]};
        for (auto const &line : getlines(in)) {
            sues.emplace_back(parse_sue(line));
        }
    }

    for (auto const &s : sues | views::enumerate) {
        if (matches(target, s.second)) {
            fmt::print("part 2: {}\n", s.first + 1);
            break;
        }
    }

    return 0;
}
