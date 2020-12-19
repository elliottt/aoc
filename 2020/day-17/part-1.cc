#include <deque>
#include <fmt/core.h>
#include <fstream>
#include <optional>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

#include "2020/day-17/dense-intmap.h"

using namespace std;
using namespace ranges;

template <> struct aoc::value_traits<char> {
    static char def() { return '.'; }
};

class pocket_dimension final {
public:
    aoc::intmap<aoc::intmap<aoc::intmap<char>>> storage;
    aoc::intmap<aoc::intmap<aoc::intmap<char>>> next;

    using slice = aoc::intmap<aoc::intmap<char>>;

    pocket_dimension() : storage{}, next{} {}

    slice &operator[](int i) { return storage[i]; }

    int active_neighbors(int x, int y, int z) {
        auto xs = views::iota(x-1, x+2);
        auto ys = views::iota(y-1, y+2);
        auto zs = views::iota(z-1, z+2);

        int acc{0};
        for (auto const &p : views::cartesian_product(xs, ys, zs)) {
            auto [a,b,c] = p;
            if (x != a || y != b || z != c) {
                if (storage[c][b][a] == '#') {
                    acc++;
                }
            }
        }

        return acc;
    }

    int total_active() {
        auto [zl,zh] = storage.bounds();
        auto [yl,yh] = storage[0].bounds();
        auto [xl,xh] = storage[0][0].bounds();

        int acc{0};
        for (auto z : views::ints(zl,zh+1)) {
            auto &s = storage[z];
            for (auto y : views::ints(yl,yh+1)) {
                auto &r = s[y];
                for (auto x : views::ints(xl,xh+1)) {
                    if (r[x] == '#') {
                        acc++;
                    }
                }
            }
        }

        return acc;
    }

    void step() {
        auto [zl,zh] = storage.bounds();
        auto [yl,yh] = storage[0].bounds();
        auto [xl,xh] = storage[0][0].bounds();

        for (auto z : views::ints(zl-1,zh+2)) {
            auto &s = storage[z];
            auto &ns = next[z];
            for (auto y : views::ints(yl-1,yh+2)) {
                auto &r = s[y];
                auto &nr = ns[y];
                for (auto x : views::ints(xl-1,xh+2)) {
                    auto active = active_neighbors(x,y,z);
                    auto c = r[x];
                    if (c == '#' && (active != 2 && active != 3)) {
                        nr[x] = '.';
                    } else if (c == '.' && active == 3) {
                        nr[x] = '#';
                    } else {
                        nr[x] = c;
                    }
                }
            }
        }

        std::swap(storage, next);
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    pocket_dimension pd{};

    {
        ifstream in{argv[1]};
        vector<string> lines{};
        ranges::copy(getlines(in), ranges::back_inserter(lines));

        auto w2 = lines.size() >> 1;
        auto &s = pd[0];
        for (auto const &[y, line] : lines | views::enumerate) {
            auto &row = s[y - w2];
            for (auto const &[x, c] : line | views::enumerate) {
                row[x - w2] = c;
            }
        }
    }

    for (int i = 0; i < 6; ++i) {
        pd.step();
    }

    fmt::print("{}\n", pd.total_active());

    return 0;
}
