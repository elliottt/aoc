#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace ranges;

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

    auto step = 1L;
    auto time = 0L;

    for (auto const &bus : busses) {
        while ((time + bus.second) % bus.first != 0) {
            time += step;
        }

        step *= bus.first;
    }

    fmt::print("part 2: {}\n", time);

    return 0;
}
