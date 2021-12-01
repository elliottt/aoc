#ifndef WIRES_H
#define WIRES_H

#include <map>
#include <string>
#include <vector>

namespace wires {

class node;

class wires {
public:
    wires();

    int get_value(int ix);
    int lookup(const std::string &name);

    void extend(const std::string &line);

    std::vector<node> state;
    std::map<std::string, int> indices;
};

class operand {
public:
    static operand reference(int value);
    static operand literal(int value);

    int get_value(wires &state) const;

    operand();

private:
    explicit operand(int value);

    int value;
};

class node {
public:
    enum class op {
        VAL,
        AND,
        OR,
        LSHIFT,
        RSHIFT,
        NOT,
    };

    op instr;
    operand left;
    operand right;

    int get_value(wires &state);

    node();
    node(op instr, operand left);
    node(op instr, operand left, operand right);
};

} // namespace wires

#endif
