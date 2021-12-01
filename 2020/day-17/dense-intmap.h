#ifndef DENSE_INTMAP_H
#define DENSE_INTMAP_H

#include <vector>

namespace aoc {

template <typename T> struct value_traits {
    static T &def() {
        return T();
    }
};

template <typename T> class intmap final {
public:
    using value_type = T;

private:
    std::pair<int, int> _bounds;
    std::vector<T> _values;

    static unsigned int map_index(int i) {
        if (i < 0) {
            return (std::abs(i) << 1) + 1;
        } else {
            return i << 1;
        }
    }

public:
    intmap() : _bounds{0, 0}, _values{} {}
    explicit intmap(size_t size) : _bounds{0, 0}, _values(size, value_traits<T>::def()) {}

    size_t size() const {
        return _values.size();
    }

    std::pair<int, int> bounds() const {
        return _bounds;
    }

    T &operator[](int i) {
        auto off = map_index(i);
        if (off >= _values.size()) {
            _values.resize(off + 1, value_traits<T>::def());
        }

        // not great
        if (i < _bounds.first) {
            _bounds.first = i;
        } else if (i > _bounds.second) {
            _bounds.second = i;
        }

        return _values[off];
    }

    friend void swap(intmap &lhs, intmap &rhs) {
        using std::swap;

        std::swap(lhs._bounds, rhs._bounds);
        std::swap(lhs._values, rhs._values);
    }
};

template <typename T> struct value_traits<intmap<T>> {
    static intmap<T> def() {
        return intmap<T>();
    }
};

} // namespace aoc

#endif
