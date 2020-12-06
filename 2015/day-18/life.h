#ifndef LIFE_H
#define LIFE_H

#include <optional>
#include <vector>

namespace aoc {

class life {
public:
    void set(int x, int y, bool val);

    bool get(int x, int y) const;
    std::optional<int> get_index(int x, int y) const;

    int neighborhood(int x, int y) const;

    void step();

    void print() const;

    life(int w, int h);

    int w;
    int h;
    std::vector<bool> cells;
    std::vector<bool> next;
};

} // namespace aoc

#endif
