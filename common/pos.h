#ifndef COMMON_POS_H
#define COMMON_POS_H

#include <cstddef>
#include <range/v3/view/cartesian_product.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/remove.hpp>
#include <range/v3/view/single.hpp>
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

    // lexicographic ordering on x, y
    bool operator<(const pos &other) const {
        if (this->x == other.x) {
            return this->y < other.y;
        } else {
            return this->x < other.x;
        }
    }

    pos north() const {
        return pos{this->x, this->y - 1};
    }

    pos east() const {
        return pos{this->x + 1, this->y};
    }

    pos south() const {
        return pos{this->x, this->y + 1};
    }

    pos west() const {
        return pos{this->x - 1, this->y};
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

    auto rows() const {
        auto ys = ranges::views::iota(0, this->height);
        return ys | ranges::views::transform([this](auto y) {
                   return ranges::views::iota(0, this->width) |
                          ranges::views::transform([y](auto x) { return pos(x, y); });
               });
    }

    auto cardinals(pos p) const {
        return ranges::views::concat(
                   ranges::views::single(p.north()),
                   ranges::views::single(p.east()),
                   ranges::views::single(p.south()),
                   ranges::views::single(p.west())) |
               ranges::views::filter([this](auto d) { return this->in_bounds(d); });
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

    bool in_bounds(pos p) const {
        return p.x >= 0 && p.x < this->width && p.y >= 0 && p.y < this->height;
    }
};

} // namespace aoc

#endif
