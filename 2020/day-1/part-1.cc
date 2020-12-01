#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <vector>

using namespace ranges;
using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    vector<int> numbers;
    {
        ifstream in{argv[1]};
        numbers = getlines(in) |
                  views::transform([](auto &line) { return stoi(line); }) |
                  to<vector>();
    }

    auto solutions =
        numbers | views::enumerate | views::transform([&numbers](auto p) {
            auto a = p.second;
            return numbers | views::drop(p.first + 1) |
                   views::transform([a](auto b) -> pair<int, int> {
                       return {a, b};
                   });
        }) |
        views::join |
        views::filter([](auto p) { return p.first + p.second == 2020; }) |
        to<vector>();

    if (!solutions.empty()) {
        fmt::print("part 1: {}\n", solutions[0].first * solutions[0].second);
    }

    return 0;
}
