#include <fmt/core.h>
#include <fstream>

#include "2015/day-7/wires.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    wires::wires state{};

    {
        ifstream in{argv[1]};
        in >> noskipws;
        while (!in.eof()) {
            string line;
            getline(in, line);
            if (line.empty()) {
                break;
            }

            state.extend(line);
        }
    }

    auto ix = state.lookup("b");
    state.state[ix] = wires::node(wires::node::op::VAL, wires::operand::literal(956));

    fmt::print("part 2: {}\n", state.get_value(state.lookup("a")));

    return 0;
}
