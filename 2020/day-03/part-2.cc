#include <fmt/core.h>
#include <fstream>
#include <functional>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

using std::ifstream, std::vector, std::string;
using namespace ranges;

int64_t count_trees(const vector<string> &input, std::function<char(const string &, int)> lookup) {
    auto cells = input | views::enumerate | views::transform([&lookup](auto p) {
                     auto &[i, line] = p;
                     return lookup(line, i);
                 });
    return ranges::count(cells, '#');
}

class lookup_wrapped {
public:
    int x;

    char operator()(const string &line, int i) {
        return line[(i * x) % line.size()];
    }

    lookup_wrapped(int x) : x{x} {}
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    ifstream in{argv[1]};
    auto input = getlines(in) | to<vector>();

    auto total = count_trees(input, lookup_wrapped{1}) * count_trees(input, lookup_wrapped{3}) *
                 count_trees(input, lookup_wrapped{5}) * count_trees(input, lookup_wrapped{7}) *
                 count_trees(input, [](auto &line, auto i) {
                     if (i % 2 == 0) {
                         return line[(i / 2) % line.size()];
                     } else {
                         return '.';
                     }
                 });

    fmt::print("part 2: {}\n", total);

    return 0;
}
