#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

struct Cell {
    int height;
    int score;
    bool visible;

    Cell(int height) : height{height}, score{0}, visible{false} {}
};

using Grid = std::vector<std::vector<Cell>>;

std::pair<size_t, size_t> bounds(const Grid &grid) {
    return std::make_pair(grid[0].size(), grid.size());
}

Cell &index(Grid &grid, size_t x, size_t y) {
    return grid[y][x];
}

const Cell &index(const Grid &grid, size_t x, size_t y) {
    return grid[y][x];
}

struct IsVisible {
    int max{-1};

    int operator()(Cell &cell) {
        if (cell.height > this->max) {
            this->max = cell.height;
            if (!cell.visible) {
                cell.visible = true;
                return 1;
            }
        }
        return 0;
    }

    void reset() {
        this->max = -1;
    }
};

int visible_in_row(Grid &grid, size_t y) {
    IsVisible check;
    auto left = ranges::accumulate(views::transform(grid[y], check), 0);
    check.reset();
    auto right = ranges::accumulate(views::transform(views::reverse(grid[y]), check), 0);
    return left + right;
}

int visible_in_col(Grid &grid, size_t x) {
    IsVisible check;
    auto top = ranges::accumulate(views::transform(grid, [&check, x](auto &row) { return check(row[x]); }), 0);
    check.reset();
    auto bottom =
        ranges::accumulate(views::transform(views::reverse(grid), [&check, x](auto &row) { return check(row[x]); }), 0);
    return top + bottom;
}

int score(const Grid &grid, size_t x, size_t y) {
    auto [width, height] = bounds(grid);
    if (x == 0 || x == width - 1 || y == 0 || y == height - 1) {
        return 0;
    }

    auto &cell = index(grid, x, y);

    auto &row = grid[y];
    auto height_x = [&row](int x) { return row[x].height; };

    int left = 0;
    for (int i = x - 1; i >= 0; --i) {
        left++;
        if (height_x(i) >= cell.height) {
            break;
        }
    }

    int right = 0;
    for (int i = x + 1; i < width; ++i) {
        right++;
        if (height_x(i) >= cell.height) {
            break;
        }
    }

    auto height_y = [&grid, x](int y) { return index(grid, x, y).height; };
    int top = 0;
    for (int i = y - 1; i >= 0; --i) {
        top++;
        if (height_y(i) >= cell.height) {
            break;
        }
    }

    int bottom = 0;
    for (int i = y + 1; i < height; ++i) {
        bottom++;
        if (height_y(i) >= cell.height) {
            break;
        }
    }

    return left * right * top * bottom;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    Grid grid;

    {
        std::ifstream in{argv[1]};
        grid = ranges::getlines(in) | views::transform([](auto &line) {
                   return views::transform(line, [](auto c) { return Cell{c - '0'}; }) | ranges::to<std::vector>;
               }) |
               ranges::to<std::vector>;
    }

    auto [width, height] = bounds(grid);
    auto visible = 0;
    for (int y = 0; y < height; ++y) {
        visible += visible_in_row(grid, y);
    }
    for (int x = 1; x < width - 1; ++x) {
        visible += visible_in_col(grid, x);
    }

    fmt::print("part 1: {}\n", visible);

    std::vector<int> scores;
    for (auto [y, row] : views::enumerate(grid)) {
        for (auto [x, cell] : views::enumerate(row)) {
            // not sure if this is true
            if (cell.visible) {
                scores.push_back(score(grid, x, y));
            }
        }
    }

    fmt::print("part 2: {}\n", *ranges::max_element(scores));

    return 0;
}
