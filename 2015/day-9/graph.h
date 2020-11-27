#ifndef GRAPH_H
#define GRAPH_H

#include <functional>
#include <string>
#include <vector>

namespace aoc {

class node {
public:
    std::string name;

    void add_edge(int other, int dist);
    void iter_edges(std::function<void(int, int)> step) const;

    node(const std::string &name);

private:
    std::vector<int> dists;
};

class graph {
public:
    graph();

    int get_node(const std::string &name);

    void add_edge(const std::string &from, const std::string &to, int dist);
    void parse_edge(const std::string &line);

    int dist_by(std::function<bool(int, int)> cmp);

    void print() const;


private:
    std::vector<node> nodes;
};

} // namespace aoc

#endif
