#include <cmath>
#include <fmt/core.h>
#include <fmt/format.h>
#include <range/v3/all.hpp>

using namespace std;
using namespace ranges;

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



    return 0;
}
