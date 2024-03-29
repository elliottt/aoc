#include <cmath>
#include <fmt/core.h>
#include <fmt/format.h>
#include <range/v3/all.hpp>

int sigma_1(int n) {
    auto acc = n;

    if (n <= 1) {
        return acc;
    }

    for (int i = 1; i <= n / 2; ++i) {
        if (n % i == 0) {
            acc += i;
        }
    }

    return acc;
}

int main() {
    // the sequence described in the problem is https://oeis.org/A326122
    // a(n) = 10*sigma_1(n)

    // the original input was 29000000, but this works just as well and allows
    // skipping out on a multiplication by 10
    auto target = 2900000;

    // this finishes pretty quickly, but is unsatisfying. it's really sensitive
    // to the start value of current, and the jump size.
    int current = 200000;
    int jump = 1 << 6;
    while (true) {
        if (sigma_1(current) > target) {
            if (jump == 1) {
                break;
            }

            current -= jump * 2;
            jump >>= 1;
        }

        current += jump;
    }

    fmt::print("part 1: {}\n", current);

    return 0;
}
