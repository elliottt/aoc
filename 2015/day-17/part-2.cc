#include <climits>
#include <fmt/core.h>
#include <fstream>
#include <functional>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

using namespace ranges;
using namespace std;

template <typename Comb, typename Proj>
auto combinations_aux(const vector<int> &sizes, const int max_count, int acc,
                      int count, int off, int def, Comb &&combine,
                      Proj &&project) {
    // prune off impossible branches
    if (acc > 150 || count > max_count || off >= sizes.size()) {
        return def;
    }

    if (acc == 150) {
        return project(count);
    }

    return combine(combinations_aux(sizes, max_count, acc + sizes[off],
                                    count + 1, off + 1, def, combine, project),
                   combinations_aux(sizes, max_count, acc, count, off + 1, def,
                                    combine, project));
}

template <typename Comb, typename Proj>
auto combinations(const vector<int> &sizes, int max_count, int def,
                  Comb &&combine, Proj &&project) {
    return combinations_aux(sizes, max_count, 0, 0, 0, def,
                            std::forward<Comb &&>(combine),
                            std::forward<Proj &&>(project));
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    vector<int> sizes{};
    {
        ifstream in{argv[1]};
        sizes = getlines(in) |
                views::transform([](auto &line) { return stoi(line); }) |
                to<vector>();
    }

    auto min_containers =
        combinations(sizes, sizes.size(), INT_MAX, ranges::min,
                     [](int count) { return count; });

    fmt::print("min containers: {}\n", min_containers);

    fmt::print("part 2: {}\n",
               combinations(sizes, min_containers, 0, std::plus{},
                            [](int count) { return 1; }));

    return 0;
}
