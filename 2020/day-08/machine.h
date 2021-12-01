#ifndef MACHINE_H
#define MACHINE_H

#include <string>
#include <vector>

namespace aoc {

enum class instr_op {
    acc,
    jmp,
    nop,
};

class instr {
public:
    bool visited;
    instr_op op;
    int arg;

    static instr parse(const std::string &str);

    void toggle();

    instr();
    instr(instr_op op, int val);
};

class machine {
public:
    int acc{0};
    std::vector<instr> instrs{};

    bool run();
    void reset();
};

} // namespace aoc

#endif
