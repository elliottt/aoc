#include <climits>
#include <deque>
#include <fmt/core.h>
#include <memory>
#include <range/v3/all.hpp>
#include <regex>
#include <string>
#include <vector>

#include "graph.h"

namespace views = ranges::views;

namespace aoc {

node::node(const std::string &name) : name{name}, edges{} {}

void node::add_edge(id other, int weight) {
    if (edges.size() <= other) {
        edges.resize(other + 1, 0);
    }
    edges[other] = weight;
}

graph::graph() : nodes{} {}

node::id graph::get_node(const std::string &name) {
    auto it = ranges::find_if(nodes, [&name](auto &n) { return n.name == name; });
    if (it == nodes.end()) {
        auto ix = nodes.size();
        nodes.emplace_back(name);
        return ix;
    } else {
        return std::distance(nodes.begin(), it);
    }
}

void graph::add_edge(node::id from, node::id to, int weight) {
    nodes[from].add_edge(to, weight);
}

void graph::parse_edge(const std::string &line) {
    auto words = line | views::tokenize(std::regex{"[\\w]+"}) | ranges::to<std::vector<std::string>>();

    auto who = words[0];
    auto other = words.back();
    auto sign = words[2] == "gain" ? 1 : -1;
    auto amount = stoi(words[3]);

    auto wix = get_node(who);
    auto oix = get_node(other);
    add_edge(wix, oix, sign * amount);
}

int graph::pair_change(node::id a, node::id b) const {
    return nodes[a].edges[b] + nodes[b].edges[a];
}

int graph::max_change() const {

    struct path {
        node::id id;
        int change;
        std::shared_ptr<path> parent;

        path(node::id id, int change, std::shared_ptr<path> &&parent) : id{id}, change{change}, parent{parent} {}

        bool seen(node::id other) {
            return id == other || (parent && parent->seen(other));
        }

        path *first() {
            path *res = this;
            while (res->parent != nullptr) {
                res = res->parent.get();
            }
            return res;
        }

        void print(const graph &g) {
            auto prev_id = first()->id;
            auto *cursor = this;
            while (cursor->parent != nullptr) {
                auto next_id = cursor->parent->id;
                fmt::print(
                    " {} <{}> {} ",
                    g.nodes[cursor->id].edges[prev_id],
                    g.nodes[cursor->id].name,
                    g.nodes[cursor->id].edges[next_id]);

                prev_id = cursor->id;
                cursor = cursor->parent.get();
            }

            fmt::print(
                " {} <{}> {}\n",
                g.nodes[cursor->id].edges[prev_id],
                g.nodes[cursor->id].name,
                g.nodes[cursor->id].edges[id]);
        }
    };

    std::deque<std::shared_ptr<path>> work{};

    auto push_work = [*this, &work](node::id id, std::shared_ptr<path> parent) {
        int change = 0;
        if (parent != nullptr) {
            change += parent->change + pair_change(id, parent->id);
        }
        auto ptr = make_shared<path>(id, change, std::move(parent));
        work.emplace_back(std::move(ptr));
    };

    for (auto i : views::ints(0, static_cast<int>(nodes.size()))) {
        push_work(i, nullptr);
    }

    auto best = INT_MIN;

    while (!work.empty()) {
        auto current = work.front();
        work.pop_front();

        bool done = true;
        for (auto oid : views::ints(0, static_cast<int>(nodes[current->id].edges.size()))) {
            if (current->seen(oid)) {
                continue;
            }

            done = false;
            push_work(oid, current);
        }

        if (done) {
            auto first = current->first()->id;
            auto change = current->change + pair_change(current->id, first);
            best = std::max(best, change);
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
