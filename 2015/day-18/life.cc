#include <range/v3/all.hpp>
#include <fmt/core.h>
#include <tuple>

#include "life.h"

using namespace std;
using namespace ranges;

namespace aoc {

life::life(int w, int h) : w{w}, h{h}, cells(w * h, false) {}

bool life::get(int x, int y) const {
    if (x < 0 || x >= w || y < 0 || y >= h) {
        return false;
    } else {
        return cells.at(y * w + x);
    }
}

void life::set(int x, int y, bool val) {
    if (x >= 0 && x < w && y >= 0 && y < h) {
        cells[y * w + x] = val;
    }
}

int life::neighborhood(int x, int y) const {
    auto xs = views::ints(x-1, x+2);
    auto ys = views::ints(y-1, y+2);

    return ranges::count_if(views::cartesian_product(xs, ys),
        [*this, x, y](auto p) {
            auto &[a,b] = p;
            if (a != x || b != y) {
                return get(a,b);
            } else {
                return false;
            }
        });
}

void life::step() {
    for (auto y : views::ints(0, h)) {
        for (auto x : views::ints(0, w)) {
            auto n = neighborhood(x,y);
            auto on = get(x,y);
            if (on) {
                set(x,y,n == 2 || n == 3);
            } else {
                set(x,y,n == 3);
            }
        }
    }
}

void life::print() const {
    for (auto y: views::ints(0, h)) {
        for (auto x : views::ints(0, w)) {
            if (get(x,y)) {
                fmt::print("#");
            } else {
                fmt::print(".");
            }
        }
        fmt::print("\n");
    }
}

} // namespace aoc
