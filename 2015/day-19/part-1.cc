#include <cctype>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fstream>
#include <map>
#include <range/v3/all.hpp>
#include <regex>
#include <set>
#include <vector>

using namespace ranges;
using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    map<string, set<string>> subs;
    string input;

    {
        ifstream in{argv[1]};
        auto lines = getlines(in) | to<vector>();

        for (auto &line : lines | views::delimit("")) {
            auto pos = line.find(" => ");
            auto key = line.substr(0, pos);
            auto value = line.substr(pos + 4);
            subs[key].insert(value);
        }

        input = lines.back();
    }

    set<string> molecules;

    for (auto &sub : subs) {
        for (auto &match : input | views::tokenize(regex{"[[:upper:]][[:lower:]]*"})) {
            if (sub.first == match.str()) {
                auto start = std::distance(input.begin(), match.first);
                for (auto &replacement : sub.second) {
                    auto copy = input;
                    copy.replace(start, match.length(), replacement);
                    molecules.insert(copy);
                }
            }
        }
    }

    fmt::print("part 1: {}\n", molecules.size());

    return 0;
}
