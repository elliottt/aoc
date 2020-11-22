#ifndef LINES_H
#define LINES_H

namespace aoc {

struct point {
    int x;
    int y;
};

int distance(const point &a, const point &b) noexcept;

}

#endif
