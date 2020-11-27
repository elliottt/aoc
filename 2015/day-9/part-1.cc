#include <fstream>
#include <fmt/core.h>
#include <range/v3/all.hpp>
#include <vector>
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

    fmt::print("part 1: {}\n", g.dist_by(ranges::less{}));

    return 0;
}
