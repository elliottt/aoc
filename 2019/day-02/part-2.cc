#include <fmt/core.h>

#include "2019/intcode/intcode.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    auto initial = intcode::machine::load(argv[1]);
    intcode::machine program{};

    for (int noun = 0; noun < 100; ++noun) {
        for (int verb = 0; verb < 100; ++verb) {
            program = initial;
            program.write(1, noun);
            program.write(2, verb);
            program.run();
            if (program.read(0) == 19690720) {
                fmt::print("Result: {:02}{:02}\n", noun, verb);
                return 0;
            }
        }
    }

    return 0;
}
