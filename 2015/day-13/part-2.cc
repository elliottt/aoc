#include <cmath>
#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>

#include "2015/day-13/graph.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    aoc::graph g;

    {
        ifstream in{argv[1]};
        for (auto &line : ranges::getlines(in)) {
            g.parse_edge(line);
        }
    }

    auto self = g.get_node("self");
    for (auto i : ranges::views::ints(0, static_cast<int>(g.nodes.size()))) {
        g.add_edge(self, i, 0);
        g.add_edge(i, self, 0);
    }

    fmt::print("part 2: {}\n", g.max_change());

    return 0;
}
