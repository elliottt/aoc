#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>

#include "2015/day-9/graph.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    aoc::graph g{};

    {
        ifstream in{argv[1]};
        in >> noskipws;
        string line;
        while (!in.eof()) {
            line.clear();
            getline(in, line);
            if (line.empty()) {
                continue;
            }

            g.parse_edge(line);
        }
    }

    fmt::print("part 2: {}\n", g.dist_by(ranges::greater{}));

    return 0;
}
