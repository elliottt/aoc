#include "intcode.h"

using namespace std;
namespace fs = std::filesystem;

namespace intcode {

machine::machine() : memory{} {}

machine::machine(vector<int> memory) : memory(memory) {}

machine machine::load(fs::path path) {
    ifstream in{path};
    return load(in);
}

machine machine::load(istream &in) {
    machine res{};
    auto eof = std::char_traits<char>::eof();
    while (true) {
        int val;
        in >> val;
        res.memory.emplace_back(val);

        if (in.get() == eof) {
            break;
        }
    }

    return res;
}

int machine::read(machine::address addr) const {
    return memory[addr];
}

void machine::write(machine::address addr, int value) {
    memory[addr] = value;
}

tuple<int, int, int> machine::decode3(int pc) {
    return {
        memory[pc + 1],
        memory[pc + 2],
        memory[pc + 3],
    };
}

void machine::run() {
    int pc = 0;
    while (true) {
        switch(static_cast<op>(memory[pc])) {
        case op::add: {
            auto [a,b,dest] = decode3(pc);
            write(dest, read(a)+read(b));
            pc += 4;
            break;
        }

        case op::mul: {
            auto [a,b,dest] = decode3(pc);
            write(dest, read(a) * read(b));
            pc += 4;
            break;
        }

        case op::halt:
            return;
        }
    }
}

}
