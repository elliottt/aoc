#include <fmt/format.h>
#include <fstream>
#include <optional>
#include <range/v3/all.hpp>
#include <set>
#include <string>
#include <vector>

#include "common/pos.h"

namespace views = ranges::views;

struct cardinal_positions;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    aoc::bounds b;
    std::vector<int> grid;
    {
        std::ifstream in{argv[1]};
        for (auto &&line : ranges::getlines(in)) {
            b.width = line.size();
            b.height++;
            for (auto c : line) {
                grid.push_back(c - '0');
            }
        }
    }

    int risk_level = 0;
    std::vector<aoc::pos> low_points;
    for (auto &&row : b.rows()) {
        for (auto p : row) {
            auto i = grid[b.index(p)];

            if (ranges::all_of(b.cardinals(p), [i, b, &grid](auto d) {
                    auto j = grid[b.index(d)];
                    return j > i;
                })) {
                low_points.emplace_back(p);
                risk_level += i + 1;
            }
        }
    }

    fmt::print("part 1: {}\n", risk_level);

    auto floodfill = [&grid, b](aoc::pos &start) {
        std::set<aoc::pos> seen;
        std::vector<std::pair<aoc::pos, int>> work{{start, -1}};

        while (!work.empty()) {
            auto [p, i] = work.back();
            work.pop_back();

            auto j = grid[b.index(p)];
            if (j == 9 || j <= i || seen.find(p) != seen.end()) {
                continue;
            }

            seen.insert(p);
            for (auto d : b.cardinals(p)) {
                work.emplace_back(d, j);
            }
        }

        return seen.size();
    };

    auto basins = views::transform(low_points, floodfill) | ranges::to<std::vector<int>> | ranges::actions::sort |
                  ranges::actions::reverse;
    fmt::print("part 2: {}\n", ranges::accumulate(views::take(basins, 3), 1, std::multiplies{}));

    return 0;
}
