#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

using namespace ranges;
using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    ifstream in{argv[1]};
    fmt::print("part 1: {}\n",
               ranges::count(getlines(in) | views::enumerate |
                                 views::transform([](auto p) {
                                     auto &[i, line] = p;
                                     auto x = i * 3;
                                     return line[x % line.size()];
                                 }),
                             '#'));

    return 0;
}
