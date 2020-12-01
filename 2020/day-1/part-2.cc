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
            auto ix = p.first;
            auto a = p.second;
            return numbers | views::drop(p.first + 1) | views::enumerate |
                   views::transform([a, ix, &numbers](auto p) {
                       auto b = p.second;
                       return numbers | views::drop(ix + p.first + 1) |
                              views::transform(
                                  [a, b](auto c) -> tuple<int, int, int> {
                                      return {a, b, c};
                                  });
                   }) |
                   views::join;
        }) |
        views::join | views::filter([](auto e) {
            auto [a, b, c] = e;
            return a + b + c == 2020;
        }) |
        to<vector>();

    if (!solutions.empty()) {
        auto [a, b, c] = solutions[0];
        fmt::print("part 1: {}\n", a * b * c);
    }

    return 0;
}
