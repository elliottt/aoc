#include <deque>
#include <fmt/core.h>
#include <fstream>
#include <map>
#include <range/v3/all.hpp>
#include <regex>
#include <set>
#include <string>

using std::ifstream, std::map, std::string, std::regex, std::set, std::deque;
using namespace ranges;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    map<string, map<string, int>> bags;

    {
        ifstream in{argv[1]};
        regex match{"[[:digit:]]+ [\\w]+ [\\w]+"};
        for (auto &line : getlines(in)) {
            auto pos = line.find(" bags contain ");
            auto key = line.substr(0, pos);

            auto &contents = bags[key];

            for (auto other : line | views::tokenize(match)) {
                string str = other.str();
                auto num = stoi(str);
                auto kind = str.substr(str.find(" ") + 1);
                contents[kind] += num;
            }
        }
    }

    set<string> result{};
    deque<string> work{"shiny gold"};

    while (!work.empty()) {
        auto head = work.front();
        work.pop_front();

        for (auto &e : bags) {
            if (result.find(e.first) == result.end()) {
                if (e.second.find(head) != e.second.end()) {
                    result.emplace(e.first);
                    work.emplace_back(e.first);
                }
            }
        }
    }

    fmt::print("part 1: {}\n", result.size());

    return 0;
}
