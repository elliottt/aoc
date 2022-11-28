#include <cctype>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fstream>
#include <map>
#include <range/v3/all.hpp>
#include <regex>
#include <set>
#include <vector>

namespace views = ranges::views;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    std::map<std::string, std::set<std::string>> subs;
    std::string input;

    {
        std::ifstream in{argv[1]};
        auto lines = ranges::getlines(in) | ranges::to<std::vector>();

        for (auto &line : lines | views::delimit("")) {
            auto pos = line.find(" => ");
            auto key = line.substr(0, pos);
            auto value = line.substr(pos + 4);
            subs[key].insert(value);
        }

        input = lines.back();
    }

    std::set<std::string> molecules;

    for (auto &sub : subs) {
        for (auto &match : input | views::tokenize(std::regex{"[[:upper:]][[:lower:]]*"})) {
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
