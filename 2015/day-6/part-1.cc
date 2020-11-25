#include <algorithm>
#include <fstream>
#include <fmt/core.h>
#include <iterator>
#include <ios>
#include <range/v3/all.hpp>
#include <regex>
#include <string>

using namespace std;

pair<int,int> parse_point(string str) {
    auto a = stoi(str);
    auto b = stoi(str.substr(str.rfind(',') + 1));
    return {a,b};
}

void interpret(vector<bool> &lights, string line) {
    vector<string> words =
        line | ranges::views::tokenize(regex{"[\\w,]+"})
             | ranges::to<vector<string>>();

    if (words[0] == "toggle") {
        auto [x1,y1] = parse_point(words[1]);
        auto [x2,y2] = parse_point(words[3]);

        for (auto y = y1; y <= y2; ++y) {
            auto start = y * 1000;
            for (auto ix = start+x1; ix <= start + x2; ++ix) {
                lights[ix] = !lights[ix];
            }
        }
    } else {
        bool to = words[1] == "on";
        auto [x1,y1] = parse_point(words[2]);
        auto [x2,y2] = parse_point(words[4]);

        for (auto y = y1; y <= y2; ++y) {
            auto start = lights.begin() + y * 1000;
            std::fill(start + x1, start + x2 + 1, to);
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    vector<bool> lights(1000*1000, false);

    string input;
    {
        ifstream in{argv[1]};
        in >> noskipws;
        ranges::copy(ranges::istream<char>(in), ranges::back_inserter(input));
    }

    for (auto line : input | ranges::views::tokenize(regex{".*\n"})) {
        interpret(lights, line);
    }

    fmt::print("part 1: {}\n", ranges::count(lights, true));

    return 0;
}
