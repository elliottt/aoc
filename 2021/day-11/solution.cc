#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

#include "common/pos.h"

using grid = std::vector<int>;

uint64_t step(aoc::bounds b, grid &octopi) {
    uint64_t flashes = 0;

    std::vector<int> work(b.size(), 1);
    std::vector<int> next(b.size(), 0);

    while (ranges::any_of(work, [](auto i) { return i > 0; })) {
        ranges::fill(next, 0);

        for (auto p : b.positions()) {
            auto ix = b.index(p);
            if (work[ix] != 0) {
                auto &octopus = octopi[ix];
                auto before = octopus;
                octopus += work[ix];
                if (before <= 9 && octopus > 9) {
                    flashes++;
                    for (auto n : b.neighbors(p)) {
                        next[b.index(n)]++;
                    }
                }
            }
        }

        std::swap(work, next);
    }

    for (auto &o : octopi) {
        if (o > 9) {
            o = 0;
        }
    }

    return flashes;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    aoc::bounds b;
    grid input;
    {
        std::ifstream in{argv[1]};
        for (auto line : ranges::getlines(in)) {
            b.width = line.size();
            b.height++;
            for (auto digit : line) {
                input.push_back(static_cast<int>(digit - '0'));
            }
        }
    }

    {
        auto octopi = input;
        uint64_t flashes = 0;
        for (auto i = 0; i < 100; i++) {
            flashes += step(b, octopi);
        }

        fmt::print("part 1: {}\n", flashes);
    }

    {
        auto octopi = input;

        int i = 0;
        while (true) {
            i++;
            if (step(b, octopi) == octopi.size()) {
                break;
            }
        }

        fmt::print("part 2: {}\n", i);
    }

    return 0;
}
