#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace ranges;

class board {
public:
    vector<string> current;
    vector<string> next;

    board() : current{}, next{} {}
    board(const vector<string> &lines) : current{lines}, next{lines} {}

    char fetch(int x, int y) const {
        if (y >= 0 && y < current.size()) {
            auto &row = current[y];
            if (x >= 0 && x < row.size()) {
                return row[x];
            }
        }
        return '.';
    }

    int neighbors(int x, int y) const {
        int count{0};
        for (auto i : views::ints(x-1, x+2)) {
            for (auto j : views::ints(y-1, y+2)) {
                if (i == x && j == y) {
                    continue;
                }

                if (fetch(i,j) == '#') {
                    ++count;
                }
            }
        }
        return count;
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
                } else if (c == '#' && occ >= 4) {
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

    fmt::print("part 1: {}\n", b.occupied());

    return 0;
}
