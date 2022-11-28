#include <string>
#include <vector>

#include "2020/day-08/machine.h"

namespace aoc {

instr::instr() : visited{false}, op{instr_op::nop}, arg{0} {}

instr::instr(instr_op op, int arg) : visited{false}, op{op}, arg{arg} {}

instr instr::parse(const std::string &str) {
    instr res{};

    auto instr = str.substr(0, 3);
    if (instr == "acc") {
        res.op = instr_op::acc;
    } else if (instr == "jmp") {
        res.op = instr_op::jmp;
    }

    res.arg = stoi(str.substr(4));

    return res;
}

void instr::toggle() {
    switch (op) {
    case instr_op::acc:
        break;
    case instr_op::jmp:
        op = instr_op::nop;
        break;
    case instr_op::nop:
        op = instr_op::jmp;
        break;
    }
}

bool machine::run() {
    int pc{0};
    while (pc < instrs.size()) {
        auto &i = instrs[pc];
        if (i.visited == true) {
            return false;
        }

        i.visited = true;
        switch (i.op) {
        case instr_op::acc:
            acc += i.arg;
            pc += 1;
            break;
        case instr_op::jmp:
            pc += i.arg;
            break;
        case instr_op::nop:
            pc += 1;
            break;
        }
    }

    return true;
}

void machine::reset() {
    acc = 0;
    for (auto &instr : instrs) {
        instr.visited = false;
    }
}

} // namespace aoc
