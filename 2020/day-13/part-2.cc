#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace ranges;

template <typename T> T gcd(T a, T b) {
    if (a < b) {
        std::swap(a, b);
    }

    while (b != 0) {
        auto t = a;
        a = b;
        b = t % b;
    }

    return a;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    vector<pair<int64_t, int64_t>> busses{};

    {
        ifstream in{argv[1]};

        string line;
        getline(in, line);

        getline(in, line);
        ranges::copy(
            line | views::tokenize(regex{"[[:alnum:]]+"}) | views::enumerate |
                views::filter([](auto const &p) { return p.second != "x"; }) |
                views::transform([](auto const &p) -> pair<int64_t, int64_t> {
                    return {stoi(p.second), p.first};
                }),
            ranges::back_inserter(busses));
    }

    auto it =
        ranges::max_element(busses, {}, [](auto const &p) { return p.first; });
    auto step = it->first;
    auto init = it->second;
    for (auto &bus : busses) {
        bus.second -= init;
    }

    auto time = 0L;
    while (ranges::any_of(busses, [&time](auto &bus) {
        return (time + bus.second) % bus.first != 0;
    })) {
        time += step;
    }

    fmt::print("part 2: {}\n", time - init);

    return 0;
}
