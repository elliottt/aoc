#ifndef COMMON_MATH_H
#define COMMON_MATH_H

#include <array>
#include <functional>
#include <range/v3/algorithm/copy.hpp>
#include <range/v3/iterator/insert_iterators.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/zip_with.hpp>

namespace aoc {

// homogenous coordinates
template <typename T, int D> class hom final {
public:
    using value_type = T;
    static constexpr int dim = D;

    std::array<value_type, D> elems;

    template <typename... Args> hom(Args... args) : elems{args...} {}

    value_type &operator[](int ix) { return elems[ix]; }

    const value_type &operator[](int ix) const { return elems[ix]; }

    hom operator+(const hom &other) const {
        hom res{*this};
        ranges::copy(ranges::views::zip_with(std::plus<value_type>(), elems,
                                             other.elems),
                     res.elems.begin());
        return res;
    }

    hom operator-(const hom &other) const {
        hom res{*this};
        ranges::copy(ranges::views::zip_with(std::minus<value_type>(), elems,
                                             other.elems),
                     res.elems.begin());
        return res;
    }

    hom operator*(const value_type val) const {
        hom res{*this};
        ranges::copy(elems | ranges::views::transform([val](auto a) { return a * val; }),
                     res.elems.begin());
        return res;
    }
};

template <typename T, int D> class vec;

template <typename T, int D> class point final {
    friend class vec<T, D>;

public:
    using value_type = T;
    static constexpr int dim = D;

private:
    point(hom<T, D + 1> &&elems) : elems{elems} {}

    hom<value_type, D + 1> elems;

public:
    template <typename... Args> point(Args... args) : elems{args..., 1} {
        static_assert(sizeof...(Args) == D,
                      "Incorrect number of args to point!");
    }

    // element access
    value_type &operator[](int ix) { return elems[ix]; }
    const value_type &operator[](int ix) const { return elems[ix]; }

    // arithmetic
    point operator+(const vec<value_type, D> &other) const;
    vec<value_type, D> operator-(const point &other) const;
};

template <typename T, int D> class vec final {
    friend class point<T, D>;

public:
    using value_type = T;
    static constexpr int dim = D;

private:
    vec(hom<value_type, D + 1> &&elems) : elems{elems} {}

    hom<value_type, D + 1> elems;

public:
    template <typename... Args> vec(Args... args) : elems{args..., 0} {
        static_assert(sizeof...(Args) == D,
                      "Incorrect number of args to vector!");
    }

    // element access
    value_type &operator[](int ix) { return elems[ix]; }
    const value_type &operator[](int ix) const { return elems[ix]; }

    // arithmetic
    vec operator+(const vec &other) const;
    vec operator-(const vec &other) const;
    vec operator*(const value_type val) const;
};

template <typename T, int D>
vec<T, D> point<T, D>::operator-(const point<T, D> &other) const {
    return vec<T, D>{elems - other.elems};
}

template <typename T, int D>
vec<T, D> vec<T, D>::operator-(const vec<T, D> &other) const {
    return vec{elems - other.elems};
}

template <typename T, int D>
point<T, D> point<T, D>::operator+(const vec<T, D> &other) const {
    return point{elems + other.elems};
}

template <typename T, int D>
vec<T, D> vec<T, D>::operator+(const vec<T, D> &other) const {
    return vec{elems - other.elems};
}

template <typename T, int D>
vec<T, D> operator*(const T val, const vec<T,D> &v) {
    return vec*val;
}

template <typename T, int D>
vec<T, D> vec<T, D>::operator*(const T val) const {
    return vec{elems*val};
}

} // namespace aoc

#endif
