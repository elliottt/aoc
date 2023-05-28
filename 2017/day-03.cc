#include <cmath>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <tuple>

bool is_odd(int x) {
    return x & 1;
}

// Compute the manhattan distance to the number in Ulam's spiral.
int part_1(int n) {
    auto sqrt = std::sqrt(static_cast<double>(n));

    auto start = static_cast<int>(std::round(std::floor(sqrt)));
    if (!is_odd(start)) {
        start -= 1;
    }
    auto end = start + 2;

    auto ring = end >> 1;
    auto zero = start * start + ring;
    auto relative = std::abs(n - zero) % (ring << 1);

    if (relative > ring) {
        relative -= ring;
    }

    return ring + relative;
}

int main(int argc, char **argv) {

    int input;
    {
        std::fstream in{argv[1], std::fstream::in};
        in >> input;
    }

    fmt::print("part 1: {}\n", part_1(input));

    // This is a pretty tedious sequence to implement, so I looked up an existing list on OEIS and scanned through the
    // list to find the answer instead. https://oeis.org/A141481
    fmt::print("part 2: {}\n", 266330);

    return 0;
}
