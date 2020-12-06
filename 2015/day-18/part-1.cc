#include <fstream>
#include <fmt/core.h>
#include <range/v3/all.hpp>

#include "life.h"

using namespace std;
using namespace ranges;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    aoc::life board{100, 100};
    {
        ifstream in{argv[1]};
        for (auto [y, line] : getlines(in) | views::enumerate) {
            for (auto [x, c] : line | views::enumerate) {
                if (c == '#') {
                    board.set(x, y, true);
                }
            }
        }
    }

    board.print();
    ranges::for_each(views::ints(0, 100), [&board](auto i) {
        fmt::print("\x1b[;H");
        board.step();
    });

    fmt::print("part 1: {}\n", ranges::count(board.cells, true));

    return 0;
}
