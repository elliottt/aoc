#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <regex>
#include <string>

using std::ifstream, std::map, std::string, std::regex;
using namespace ranges;

int nested_bags(const map<string, map<string, int>> &bags, const string &bag) {
    auto &contents = bags.find(bag)->second;
    return ranges::accumulate(contents | views::transform([&bags](auto &e) {
                                  return nested_bags(bags, e.first) * e.second;
                              }),
                              1);
}

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

    // subtract one, as we're not counting the shiny bag
    fmt::print("part 2: {}\n", nested_bags(bags, "shiny gold") - 1);

    return 0;
}
