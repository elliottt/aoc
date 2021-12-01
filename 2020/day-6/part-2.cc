#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

using std::ifstream, std::string, std::vector;
using namespace ranges;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    ifstream in{argv[1]};

    vector<string> lines{};
    auto total = ranges::accumulate(
        getlines(in) | views::split("") | views::transform([&lines](auto rng) {
            // it would be nice to avoid this, but it's not possible to traverse
            // the split range twice, and it's not obvious if it's possible ot
            // observe the entries before the join.
            lines = rng | to<vector>();

            string all = rng | views::join | to<string>() | actions::sort;

            return ranges::count_if(
                all | views::group_by([](auto a, auto b) { return a == b; }),
                [&lines](auto rng) {
                    return ranges::size(rng) == lines.size();
                });
        }),
        0);

    // TODO: there's a bug here, this is not outputting the correct answer anymore
    fmt::print("part 2: {}\n", total);

    return 0;
}
