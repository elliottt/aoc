#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

namespace aoc {

class node {
public:
    std::string name;
    std::vector<int> edges;

    using id = int;

    void add_edge(id other, int weight);

    explicit node(const std::string &name);
};

class graph {
public:
    std::vector<node> nodes;

    node::id get_node(const std::string &name);

    void add_edge(node::id from, node::id to, int weight);
    void parse_edge(const std::string &line);

    int pair_change(node::id a, node::id b) const;

    int max_change() const;

    void print() const;

    graph();
};

} // namespace aoc

#endif
