#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

using std::ifstream, std::string, std::vector;
using namespace ranges;

class board {
public:
    vector<string> current;
    vector<string> next;

    board() : current{}, next{} {}
    board(const vector<string> &lines) : current{lines}, next{lines} {}

    bool valid_coord(int x, int y) const {
        if (y >= 0 && y < current.size()) {
            return x >= 0 && x < current[y].size();
        }
        return false;
    }

    char walk_ray(int x, int y, int dx, int dy) const {
        char seen{'.'};
        while (valid_coord(x,y) && seen == '.') {
            seen = current[y][x];
            x += dx;
            y += dy;
        }
        return seen;
    }

    int neighbors(int x, int y) const {
        auto xs = views::ints(x-1, x+2);
        auto ys = views::ints(y-1, y+2);

        return ranges::count_if(views::cartesian_product(xs, ys),
            [x,y,*this](auto const &p) {
                auto [i,j] = p;
                if (x == i && y == j) {
                    return false;
                }

                int dx = i - x;
                int dy = j - y;
                return walk_ray(i,j,dx,dy) == '#';
            });
    }

    bool step() {
        bool changed{false};

        for (auto const &[y, row] : current | views::enumerate) {
            for (auto [x, c] : row | views::enumerate) {
                next[y][x] = c;

                if (c == '.') {
                    continue;
                }

                int occ = neighbors(x,y);
                if (c == 'L' && occ == 0) {
                    changed = true;
                    next[y][x] = '#';
                } else if (c == '#' && occ >= 5) {
                    changed = true;
                    next[y][x] = 'L';
                }
            }
        }

        std::swap(current, next);

        return changed;
    }

    int occupied() const {
        return ranges::accumulate(current | views::transform([](auto &row) {
            return ranges::count(row, '#');
        }), 0);
    }

    void print() {
        for (auto const &[row, nrow] : views::zip(current, next)) {
            fmt::print("{} -- {}\n", row, nrow);
        }
    }
};


int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    board b{};

    {
        ifstream in{argv[1]};
        vector<string> lines;
        ranges::copy(getlines(in), ranges::back_inserter(lines));

        b = board{lines};
    }

    int count = 0;
    for(; b.step(); ++count) {}

    fmt::print("part 2: {}\n", b.occupied());

    return 0;
}
