#include <fmt/core.h>
#include <fstream>
#include <iterator>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

#include "2020/day-08/machine.h"

using std::ifstream, std::vector;
using namespace ranges;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    aoc::machine state{};

    {
        ifstream in{argv[1]};

        state.instrs = getlines(in) | views::transform([](auto &str) { return aoc::instr::parse(str); }) | to<vector>();
    }

    state.run();
    fmt::print("part 1: {}\n", state.acc);

    return 0;
}
