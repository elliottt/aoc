#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

using grid = std::vector<int>;

struct pos final {
    int x = 0;
    int y = 0;

    pos(int x, int y) : x{x}, y{y} {}

    bool operator==(const pos &other) const {
        return this->x == other.x && this->y == other.y;
    }
};

struct bounds final {
    int width = 0;
    int height = 0;

    bounds() = default;
    bounds(int width, int height) : width{width}, height{height} {}

    size_t size() const {
        return this->width * this->height;
    }

    size_t index(pos p) const {
        return p.y * height + p.x;
    }

    auto positions() const {
        auto ys = views::iota(0, this->height);
        auto xs = views::iota(0, this->width);
        return views::cartesian_product(ys, xs) | views::transform([](auto p) {
                   auto [y, x] = p;
                   return pos(x, y);
               });
    }

    auto neighbors(pos p) const {
        auto xs = views::iota(std::max(p.x - 1, 0), std::min(this->width, p.x + 2));
        auto ys = views::iota(std::max(p.y - 1, 0), std::min(this->height, p.y + 2));
        return views::cartesian_product(ys, xs) | views::transform([](auto p) {
                   auto [y, x] = p;
                   return pos{x, y};
               }) |
               views::remove(p);
    }
};

uint64_t step(bounds b, grid &octopi) {
    uint64_t flashes = 0;

    std::vector<int> work(b.size(), 1);
    std::vector<int> next(b.size(), 0);

    while (ranges::any_of(work, [](auto i) { return i > 0; })) {
        ranges::fill(next, 0);

        for (auto p : b.positions()) {
            auto ix = b.index(p);
            if (work[ix] != 0) {
                auto &octopus = octopi[ix];
                auto before = octopus;
                octopus += work[ix];
                if (before <= 9 && octopus > 9) {
                    flashes++;
                    for (auto n : b.neighbors(p)) {
                        next[b.index(n)]++;
                    }
                }
            }
        }

        std::swap(work, next);
    }

    for (auto &o : octopi) {
        if (o > 9) {
            o = 0;
        }
    }

    return flashes;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    bounds b;
    grid input;
    {
        std::ifstream in{argv[1]};
        for (auto line : ranges::getlines(in)) {
            b.width = line.size();
            b.height++;
            for (auto digit : line) {
                input.push_back(static_cast<int>(digit - '0'));
            }
        }
    }

    {
        auto octopi = input;
        uint64_t flashes = 0;
        for (auto i = 0; i < 100; i++) {
            flashes += step(b, octopi);
        }

        fmt::print("part 1: {}\n", flashes);
    }

    {
        auto octopi = input;

        int i = 0;
        while (true) {
            i++;
            if (step(b, octopi) == octopi.size()) {
                break;
            }
        }

        fmt::print("part 2: {}\n", i);
    }

    return 0;
}
