#ifndef COMMON_INTERVAL_H
#define COMMON_INTERVAL_H

#include <algorithm>
#include <tuple>

namespace aoc {

template <typename T> struct Interval {
    T min = 0;
    T max = 0;

    Interval() = default;
    Interval(T min, T max) : min{min}, max{max} {}

    T first() const {
        return this->min;
    }

    T last() const {
        return this->max - 1;
    }

    bool empty() const {
        return this->min >= this->max;
    }

    operator bool() const {
        return !this->empty();
    }

    bool contains(T val) const {
        return this->min <= val && val < this->max;
    }

    bool contains(const Interval &other) const {
        return this->min <= other.min && other.max <= this->max;
    }

    bool overlaps(const Interval &other) const {
        return this->contains(other.min) || other.contains(this->min);
    }

    Interval merge(const Interval &other) const {
        return Interval{std::max(this->min, other.min), std::min(this->max, other.max)};
    }

    std::tuple<Interval, Interval> subtract(const Interval &other) const {
        Interval left{this->min, other.min};
        Interval right{other.max, this->max};

        return {left, right};
    }

    Interval operator+(T val) const {
        return Interval{this->min + val, this->max + val};
    }

    Interval operator-(T val) const {
        return Interval{this->min - val, this->max - val};
    }
};

} // namespace aoc

#endif
