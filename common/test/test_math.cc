#include <doctest.h>
#include <fmt/core.h>

#include "common/math.h"

using namespace aoc;

TEST_CASE("point") {
    point<int, 2> foo{0,0};
    vec<int, 2> dir{1,1};

    auto res = foo+dir;

    CHECK_EQ(res[0], 1);
    CHECK_EQ(res[1], 1);
}
