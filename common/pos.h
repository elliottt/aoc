#ifndef COMMON_POS_H
#define COMMON_POS_H

#include <cstddef>
#include <range/v3/view/cartesian_product.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/remove.hpp>
#include <range/v3/view/transform.hpp>

namespace aoc {

struct pos final {
    int x = 0;
    int y = 0;

    pos() = default;
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
        auto ys = ranges::views::iota(0, this->height);
        auto xs = ranges::views::iota(0, this->width);
        return ranges::views::cartesian_product(ys, xs) | ranges::views::transform([](auto p) {
                   auto [y, x] = p;
                   return pos(x, y);
               });
    }

    auto neighbors(pos p) const {
        auto xs = ranges::views::iota(std::max(p.x - 1, 0), std::min(this->width, p.x + 2));
        auto ys = ranges::views::iota(std::max(p.y - 1, 0), std::min(this->height, p.y + 2));
        return ranges::views::cartesian_product(ys, xs) | ranges::views::transform([](auto p) {
                   auto [y, x] = p;
                   return pos{x, y};
               }) |
               ranges::views::remove(p);
    }
};

} // namespace aoc

#endif
