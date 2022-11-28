#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include <fmt/core.h>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/istream.hpp>
#include <range/v3/view/transform.hpp>

namespace views = ranges::views;

int compute_fuel(int mass) {
    return std::max(0, (mass / 3) - 2);
}

int compute_fuel_extra(int mass) {
    int fuel = compute_fuel(mass);

    int extra = fuel;
    while (true) {
        extra = compute_fuel(extra);
        if (extra <= 0) {
            break;
        }

        fuel += extra;
    }

    return fuel;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::ifstream file{argv[1]};
    int module_fuel = ranges::accumulate(ranges::istream<int>(file) | views::transform(compute_fuel_extra), 0);

    fmt::print("Total fuel required: {}\n", module_fuel);

    return 0;
}
