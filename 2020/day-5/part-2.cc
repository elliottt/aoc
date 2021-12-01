#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

using std::ifstream, std::string, std::vector;
using namespace ranges;

int parse_seat_row(const string &str) {
    int row_val = 0;
    for (auto c : str.substr(0, 7)) {
        row_val <<= 1;
        if (c == 'B') {
            row_val |= 1;
        }
    }

    int col_val = 0;
    for (auto c : str.substr(7, 3)) {
        col_val <<= 1;
        if (c == 'R') {
            col_val |= 1;
        }
    }

    return row_val * 8 + col_val;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    ifstream in{argv[1]};
    auto row_ids = getlines(in) | views::transform(parse_seat_row) | to<vector>() | actions::sort;

    auto sol = views::zip(row_ids, row_ids | views::drop(1)) |
               views::filter([](auto p) { return p.first + 1 != p.second; }) |
               views::transform([](auto p) { return p.first + 1; });

    fmt::print("part 2: {}\n", *ranges::begin(sol));

    return 0;
}
