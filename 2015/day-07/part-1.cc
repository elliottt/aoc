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

    fmt::print("part 1: {}\n", state.get_value(state.lookup("a")));

    return 0;
}
