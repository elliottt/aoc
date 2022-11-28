#include <algorithm>
#include <fmt/core.h>
#include <fstream>
#include <ios>
#include <iterator>
#include <range/v3/all.hpp>
#include <regex>
#include <string>

std::pair<int, int> parse_point(std::string str) {
    auto a = stoi(str);
    auto b = stoi(str.substr(str.rfind(',') + 1));
    return {a, b};
}

void interpret(std::vector<int> &lights, std::string line) {
    std::vector<std::string> words =
        line | ranges::views::tokenize(std::regex{"[\\w,]+"}) | ranges::to<std::vector<std::string>>();

    if (words[0] == "toggle") {
        auto [x1, y1] = parse_point(words[1]);
        auto [x2, y2] = parse_point(words[3]);

        for (auto y = y1; y <= y2; ++y) {
            auto start = y * 1000;
            for (auto ix = start + x1; ix <= start + x2; ++ix) {
                lights[ix] += 2;
            }
        }
    } else {
        int amount = words[1] == "on" ? 1 : -1;
        auto [x1, y1] = parse_point(words[2]);
        auto [x2, y2] = parse_point(words[4]);

        for (auto y = y1; y <= y2; ++y) {
            auto start = y * 1000;
            for (auto ix = start + x1; ix <= start + x2; ++ix) {
                lights[ix] = std::max(0, lights[ix] + amount);
            }
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    std::vector<int> lights(1000 * 1000, 0);

    std::string input;
    {
        std::ifstream in{argv[1]};
        in >> std::noskipws;
        ranges::copy(ranges::istream<char>(in), ranges::back_inserter(input));
    }

    for (auto line : input | ranges::views::tokenize(std::regex{".*\n"})) {
        interpret(lights, line);
    }

    fmt::print("part 0: {}\n", ranges::accumulate(lights, 0));

    return 0;
}
