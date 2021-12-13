#include <fmt/format.h>
#include <fstream>
#include <optional>
#include <range/v3/all.hpp>
#include <set>
#include <string>
#include <vector>

namespace views = ranges::views;

struct cardinal_positions;

struct pos {
    int x;
    int y;

    pos(int x, int y) : x{x}, y{y} {}

    cardinal_positions cardinals() const;

    bool operator==(const pos &other) const {
        return this->x == other.x && this->y == other.y;
    }

    bool operator<(const pos &other) const {
        if (this->x == other.x) {
            return this->y < other.y;
        } else {
            return this->x < other.x;
        }
    }
};

struct cardinal_positions {
    pos north;
    pos east;
    pos south;
    pos west;
};

cardinal_positions pos::cardinals() const {
    return cardinal_positions{
        pos{this->x, this->y - 1},
        pos{this->x + 1, this->y},
        pos{this->x, this->y + 1},
        pos{this->x - 1, this->y},
    };
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::vector<std::vector<int>> grid;
    {
        std::ifstream in{argv[1]};
        for (auto &&line : ranges::getlines(in)) {
            auto &row = grid.emplace_back();
            for (auto c : line) {
                row.push_back(c - '0');
            }
        }
    }

    int risk_level = 0;
    std::vector<pos> low_points;
    for (const auto &[y, row] : views::enumerate(grid)) {
        for (auto [x, i] : views::enumerate(row)) {
            if (x > 0 && row[x - 1] <= i) {
                continue;
            }

            if (x + 1 < row.size() && row[x + 1] <= i) {
                continue;
            }

            if (y > 0 && grid[y - 1][x] <= i) {
                continue;
            }

            if (y + 1 < grid.size() && grid[y + 1][x] <= i) {
                continue;
            }

            low_points.emplace_back(x, y);
            risk_level += i + 1;
        }
    }

    fmt::print("part 1: {}\n", risk_level);

    auto lookup = [&grid](pos p) -> int {
        if (p.x < 0 || p.x >= grid.front().size() || p.y < 0 || p.y >= grid.size()) {
            return 9;
        }
        return grid[p.y][p.x];
    };

    auto floodfill = [&lookup](pos &start) {
        std::set<pos> seen;
        std::vector<std::pair<pos, int>> work{{start, -1}};

        while (!work.empty()) {
            auto [p, i] = work.back();
            work.pop_back();

            auto j = lookup(p);
            if (j == 9 || j <= i || seen.find(p) != seen.end()) {
                continue;
            }

            seen.insert(p);
            auto [n, e, s, w] = p.cardinals();
            work.emplace_back(n, j);
            work.emplace_back(e, j);
            work.emplace_back(s, j);
            work.emplace_back(w, j);
        }

        return seen.size();
    };

    auto basins = views::transform(low_points, floodfill) | ranges::to<std::vector<int>> | ranges::actions::sort |
                  ranges::actions::reverse;
    fmt::print("part 2: {}\n", ranges::accumulate(views::take(basins, 3), 1, std::multiplies{}));

    return 0;
}
