#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

using namespace ranges;
using namespace std;

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
    auto row_ids = getlines(in) | views::transform(parse_seat_row) | to<vector>();

    fmt::print("part 1: {}\n", *ranges::max_element(row_ids));

    return 0;
}
