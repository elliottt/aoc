#include <cmath>

#include "lines.h"

using namespace std;

namespace aoc {

int distance(const point &a, const point &b) noexcept {
    return abs(a.x - b.x) + abs(a.y - b.y);
}

} // namespace aoc
