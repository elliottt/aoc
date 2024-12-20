#include <array>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

struct Direction {
    int dx;
    int dy;
};

struct Point {
    int x;
    int y;

    Point move_by(Direction &dir) const {
        return Point{this->x + dir.dx, this->y + dir.dy};
    }

    char lookup(std::span<std::string> lines) const {
        if (this->y < 0 || this->y >= lines.size()) {
            return '.';
        }

        auto &line = lines[this->y];
        if (this->x < 0 || this->x >= line.size()) {
            return '.';
        }

        return line[this->x];
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::vector<std::string> lines;

    {
        std::ifstream in{argv[1]};
        lines = ranges::getlines(in) | ranges::to<std::vector>;
    }

    {
        std::array<Direction, 8> dirs{
            Direction{-1, 0},
            Direction{-1, 1},
            Direction{0, 1},
            Direction{1, 1},
            Direction{1, 0},
            Direction{1, -1},
            Direction{0, -1},
            Direction{-1, -1},
        };
        int found = 0;
        for (auto [row, line] : lines | views::enumerate) {
            for (auto [col, c] : line | views::enumerate) {
                if (c != 'X') {
                    continue;
                }

                for (auto &dir : dirs) {
                    Point p(col, row);
                    p = p.move_by(dir);
                    if (p.lookup(lines) != 'M') {
                        continue;
                    }
                    p = p.move_by(dir);
                    if (p.lookup(lines) != 'A') {
                        continue;
                    }
                    p = p.move_by(dir);
                    if (p.lookup(lines) != 'S') {
                        continue;
                    }
                    found += 1;
                }
            }
        }

        fmt::print("part 1: {}\n", found);
    }

    {
        std::array<Direction, 4> times{
            Direction{-1, -1},
            Direction{1, -1},
            Direction{1, 1},
            Direction{-1, 1},
        };

        int found = 0;
        for (auto [row, line] : lines | views::enumerate) {
            for (auto [col, c] : line | views::enumerate) {
                if (c != 'A') {
                    continue;
                }

                Point p(col, row);
                auto tl = p.move_by(times[0]).lookup(lines);
                auto tr = p.move_by(times[1]).lookup(lines);
                auto br = p.move_by(times[2]).lookup(lines);
                auto bl = p.move_by(times[3]).lookup(lines);

                if ((tl == 'M' && br == 'S') || (tl == 'S' && br == 'M')) {
                    if ((tr == 'M' && bl == 'S') || (tr == 'S' && bl == 'M')) {
                        found += 1;
                    }
                }
            }
        }

        fmt::print("part 2: {}\n", found);
    }

    return 0;
}
