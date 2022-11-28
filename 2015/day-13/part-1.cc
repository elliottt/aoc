#include <cmath>
#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>

#include "2015/day-13/graph.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    aoc::graph g;

    {
        std::ifstream in{argv[1]};
        for (auto &line : ranges::getlines(in)) {
            g.parse_edge(line);
        }
    }

    fmt::print("part 1: {}\n", g.max_change());

    return 0;
}
