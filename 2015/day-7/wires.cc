#include <cctype>
#include <optional>
#include <range/v3/all.hpp>

#include "2015/day-7/wires.h"

using namespace std;

namespace wires {

namespace {

operand parse_operand(wires &state, const string &val) {
    if (ranges::all_of(val, [](auto c) { return isdigit(c); })) {
        return operand::literal(stoi(val));
    } else {
        return operand::reference(state.lookup(val));
    }
}

struct binop {
    string l;
    string r;
};

optional<binop> parse_binop(const string &command, const string &&op) {
    auto start = command.find(op);
    if (start == string::npos) {
        return std::nullopt;
    }

    return binop{command.substr(0, start - 1),
                 command.substr(start + 1 + op.size())};
}

optional<string> parse_prefix(const string &command, const string &&op) {
    if (command.substr(0, op.size()) != op) {
        return std::nullopt;
    }

    return command.substr(op.size() + 1);
}

} // namespace

wires::wires() : state{}, indices{} {}

int wires::get_value(int ix) {
    auto n = state[ix];
    auto val = n.get_value(*this);

    // cache values to avoid expensive recomputation
    if (n.instr != node::op::VAL) {
        state[ix] = node(node::op::VAL, operand::literal(val));
    }

    return val;
}

int wires::lookup(const string &name) {
    auto pos = indices.find(name);
    if (pos != indices.end()) {
        return pos->second;
    } else {
        int ix = state.size();
        indices[name] = ix;
        state.emplace_back();
        return ix;
    }
}

void wires::extend(const string &line) {
    auto pos = line.find("->");
    if (pos == string::npos) {
        return;
    }

    auto command = line.substr(0, pos - 1);
    auto target = line.substr(pos + 3);

    auto ix = lookup(target);
    if (auto op = parse_binop(command, "AND")) {
        state[ix] = node(node::op::AND, parse_operand(*this, op->l),
                         parse_operand(*this, op->r));
    } else if (auto op = parse_binop(command, "OR")) {
        state[ix] = node(node::op::OR, parse_operand(*this, op->l),
                         parse_operand(*this, op->r));
    } else if (auto op = parse_binop(command, "RSHIFT")) {
        state[ix] = node(node::op::RSHIFT, parse_operand(*this, op->l),
                         parse_operand(*this, op->r));
    } else if (auto op = parse_binop(command, "LSHIFT")) {
        state[ix] = node(node::op::LSHIFT, parse_operand(*this, op->l),
                         parse_operand(*this, op->r));
    } else if (auto op = parse_prefix(command, "NOT")) {
        state[ix] = node(node::op::NOT, parse_operand(*this, *op));
    } else {
        state[ix] = node(node::op::VAL, parse_operand(*this, command));
    }
}

operand::operand() : value{0} {}

operand::operand(int value) : value{value} {}

operand operand::reference(int value) { return operand(-1 - value); }

operand operand::literal(int value) { return operand(value); }

int operand::get_value(wires &state) const {
    if (value >= 0) {
        return value;
    } else {
        auto ix = -(1 + value);
        return state.get_value(ix);
    }
}

node::node(op instr, operand left, operand right)
    : instr{instr}, left{left}, right{right} {}

node::node() : node(op::VAL, operand{}, operand{}) {}

node::node(op instr, operand left) : node(instr, left, operand{}) {}

int node::get_value(wires &state) {
    switch (instr) {
    case op::VAL:
        return left.get_value(state);

    case op::AND:
        return left.get_value(state) & right.get_value(state);

    case op::OR:
        return left.get_value(state) | right.get_value(state);

    case op::LSHIFT:
        return left.get_value(state) << right.get_value(state);

    case op::RSHIFT:
        return left.get_value(state) >> right.get_value(state);

    case op::NOT:
        return ~left.get_value(state);
    }
}

} // namespace wires
