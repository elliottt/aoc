#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

#include "2020/day-8/machine.h"

using std::ifstream, std::vector;
using namespace ranges;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    aoc::machine state{};

    {
        ifstream in{argv[1]};

        state.instrs =
            getlines(in) |
            views::transform([](auto &str) { return aoc::instr::parse(str); }) |
            to<vector>();
    }

    // run it once to mark instructions
    state.run();

    // intentionally cache the instruction indices so that the lazy range
    // doesn't interleave effects with the run/reset behavior of the machine.
    auto indices =
        state.instrs | views::enumerate | views::filter([](auto const &p) {
            return p.second.visited && (p.second.op == aoc::instr_op::jmp ||
                                        p.second.op == aoc::instr_op::nop);
        }) |
        views::transform([](auto const &p) { return p.first; }) | to<vector>();

    for (auto ix : indices) {
        auto &instr = state.instrs[ix];
        instr.toggle();

        state.reset();
        if (state.run()) {
            fmt::print("part 2: {}\n", state.acc);
            break;
        }

        instr.toggle();
    }

    return 0;
}
