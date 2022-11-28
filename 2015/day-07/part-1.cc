#include <fmt/core.h>
#include <fstream>

#include "2015/day-07/wires.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    wires::wires state{};

    {
        std::ifstream in{argv[1]};
        in >> std::noskipws;
        while (!in.eof()) {
            std::string line;
            getline(in, line);
            if (line.empty()) {
                break;
            }

            state.extend(line);
        }
    }

    fmt::print("part 1: {}\n", state.get_value(state.lookup("a")));

    return 0;
}
