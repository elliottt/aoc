#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <thread>

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

    ranges::for_each(views::ints(0, 100), [&board](auto i) {
        board.step();

        // these lights are stuck
        board.set(0, 0, true);
        board.set(0, 99, true);
        board.set(99, 0, true);
        board.set(99, 99, true);
    });

    fmt::print("part 1: {}\n", ranges::count(board.cells, true));

    return 0;
}
