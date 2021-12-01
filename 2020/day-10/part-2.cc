#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>

using std::ifstream, std::string, std::vector;
using namespace ranges;

// once i realized that the result would be larger than an int i updated
// everywhere **except** the return type of this function. that led to an hour
// of confused debugging, wondering why the heck my answer was wrong when it
// passed on the test inputs.
int64_t combinations(vector<int64_t> &cache, const vector<int64_t> &adapters, int ix) {
    if (cache[ix] != -1) {
        return cache[ix];
    }

    if (ix == adapters.size() - 1) {
        return 1;
    }

    int64_t a = adapters[ix];

    auto rng = adapters | views::enumerate | views::drop(ix + 1) |
               views::take_while([a](auto const &p) { return (p.second - a) <= 3; }) |
               views::transform([&cache, &adapters](auto const &p) { return combinations(cache, adapters, p.first); });

    int64_t res = ranges::accumulate(rng, 0L);

    cache[ix] = res;

    return res;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    vector<int64_t> adapters{};
    {
        ifstream in{argv[1]};
        ranges::copy(
            getlines(in) | views::transform([](auto &str) { return stol(str); }),
            ranges::back_inserter(adapters));
    }

    adapters.emplace_back(*ranges::max_element(adapters) + 3);
    adapters.emplace_back(0);

    ranges::sort(adapters);

    vector<int64_t> cache(adapters.size(), -1);
    fmt::print("part 2: {}\n", combinations(cache, adapters, 0));

    return 0;
}
