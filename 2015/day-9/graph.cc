#include <fmt/core.h>
#include <range/v3/all.hpp>

#include "graph.h"

using namespace std;

namespace aoc {

node::node(const string &name) : name{name} {}

void node::add_edge(int other, int dist) {
    if (other >= dists.size()) {
        dists.resize(other + 1, 0);
    }
    dists[other] = dist;
}

void node::iter_edges(function<void(int, int)> step) const {
    ranges::for_each(dists | ranges::views::enumerate,
                     [*this, &step](auto const p) { step(p.first, p.second); });
}

graph::graph() : nodes{} {}

int graph::get_node(const string &name) {
    auto it = ranges::find_if(
        nodes, [&name](auto const &n) { return n.name == name; });

    if (it == nodes.end()) {
        auto ix = nodes.size();
        nodes.emplace_back(name);
        return ix;
    } else {
        return distance(nodes.begin(), it);
    }
}

void graph::add_edge(const string &from, const string &to, int dist) {
    auto fix = get_node(from);
    auto tix = get_node(to);
    nodes[fix].add_edge(tix, dist);
    nodes[tix].add_edge(fix, dist);
}

void graph::parse_edge(const string &line) {
    vector<string> words = line | ranges::views::tokenize(regex{"[\\w]+"}) |
                           ranges::to<vector<string>>();

    // the last word is at 3 because the regex doesn't match `=`
    add_edge(words[0], words[2], stoi(words[3]));
}

int graph::dist_by(function<bool(int, int)> cmp) {
    vector<int> dists{};

    struct path {
        int ix;
        shared_ptr<path> parent;
        int distance;

        path(int ix, shared_ptr<path> parent, int distance)
            : ix{ix}, parent{parent}, distance{distance} {}

        bool seen(int other) {
            return other == ix || (parent && parent->seen(other));
        }
    };

    deque<shared_ptr<path>> work{};

    auto push_work = [*this, &work](int ix, shared_ptr<path> parent,
                                    int distance) {
        if (parent) {
            distance += parent->distance;
        }

        auto ptr = make_shared<path>(ix, std::move(parent), distance);
        work.emplace_back(ptr);
    };

    // seed the work queue with all the nodes
    for (auto ix : ranges::views::ints(0, static_cast<int>(nodes.size()))) {
        push_work(ix, nullptr, 0);
    }

    auto total = -1;

    while (!work.empty()) {
        auto current = work.front();
        work.pop_front();

        bool path_finished = true;
        nodes[current->ix].iter_edges(
            [&path_finished, &push_work, &current](auto other, auto dist) {
                if (!current->seen(other)) {
                    path_finished = false;
                    push_work(other, current, dist);
                }
            });

        if (path_finished) {
            if (total < 0 || cmp(current->distance, total)) {
                total = current->distance;
            }
        }
    }

    return total;
}

void graph::print() const {
    for (auto const &n : nodes) {
        fmt::print("{}:\n", n.name);
        n.iter_edges([*this](auto ix, auto dist) {
            fmt::print("  -> {} ({})\n", nodes[ix].name, dist);
        });
    }
}

} // namespace aoc
