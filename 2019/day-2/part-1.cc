#include <fmt/core.h>

#include "2019/intcode/intcode.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    auto program = intcode::machine::load(argv[1]);
    program.write(1, 12);
    program.write(2, 2);
    program.run();
    fmt::print("Result: {}\n", program.read(0));

    return 0;
}
