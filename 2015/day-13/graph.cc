#include <climits>
#include <deque>
#include <fmt/core.h>
#include <memory>
#include <range/v3/all.hpp>
#include <regex>
#include <string>
#include <vector>

#include "graph.h"

using namespace ranges;
using namespace std;

namespace aoc {

node::node(const string &name) : name{name}, edges{} {}

void node::add_edge(id other, int weight) {
    if (edges.size() <= other) {
        edges.resize(other + 1, 0);
    }
    edges[other] = weight;
}

graph::graph() : nodes{} {}

node::id graph::get_node(const string &name) {
    auto it =
        ranges::find_if(nodes, [&name](auto &n) { return n.name == name; });
    if (it == nodes.end()) {
        auto ix = nodes.size();
        nodes.emplace_back(name);
        return ix;
    } else {
        return std::distance(nodes.begin(), it);
    }
}

void graph::parse_edge(const string &line) {
    auto words = line | views::tokenize(regex{"[\\w]+"}) | to<vector<string>>();

    auto who = words[0];
    auto other = words.back();
    auto sign = words[2] == "gain" ? 1 : -1;
    auto amount = stoi(words[3]);

    auto wix = get_node(who);
    auto oix = get_node(other);
    nodes[wix].add_edge(oix, sign * amount);
}

int graph::max_change() const {

    struct path {
        node::id id;
        int change;
        shared_ptr<path> parent;

        path(node::id id, int change, shared_ptr<path> &&parent) : id{id}, change{change}, parent{parent} {}

        bool seen(node::id other) {
            return id == other || (parent && parent->seen(other));
        }
    };

    deque<shared_ptr<path>> work{};

    auto push_work = [&work](node::id id, int change, shared_ptr<path> parent) {
        if (parent != nullptr) {
            change += parent->change;
        }
        auto ptr = make_shared<path>(id, change, std::move(parent));
        work.emplace_back(std::move(ptr));
    };

    for (auto i : views::ints(0, static_cast<int>(nodes.size()))) {
        push_work(i, 0, nullptr);
    }

    auto best = INT_MIN;

    while (!work.empty()) {
        auto current = work.front();
        work.pop_front();

        bool done = true;
        for (auto const &[oid, weight] : nodes[current->id].edges | views::enumerate) {
            if (current->seen(oid)) {
                continue;
            }

            done = false;
            push_work(oid, weight, current);
        }

        if (done) {
            best = std::max(best, current->change);
        }
    }

    return best;
}

void graph::print() const {
    for (auto const &[ix, n] : nodes | views::enumerate) {
        fmt::print("({}) {}:\n", ix, n.name);
        for (auto const &[oix, dist] : n.edges | views::enumerate) {
            fmt::print("  ({}) {} {}\n", oix, nodes[oix].name, dist);
        }
    }
}

} // namespace aoc
