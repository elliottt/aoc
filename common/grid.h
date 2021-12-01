#ifndef COMMON_GRID_H
#define COMMON_GRID_H

#include <vector>

#include "math.h"

namespace aoc {

class coord;

template <typename T> class grid {
public:
    using value_type = T;

    value_type &get(const coord &c);
    const value_type &get(const coord &c) const;

    grid(int width, int height);

private:
    vector<value_type> cells;
};

} // namespace aoc

#endif
