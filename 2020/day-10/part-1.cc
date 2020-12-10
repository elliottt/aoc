#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>

using namespace std;
using namespace ranges;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    vector<int> adapters{};
    {
        ifstream in{argv[1]};
        ranges::copy(getlines(in) |
                         views::transform([](auto &str) { return stoi(str); }),
                     ranges::back_inserter(adapters));
    }

    adapters.emplace_back(*ranges::max_element(adapters) + 3);
    adapters.emplace_back(0);

    ranges::sort(adapters);

    int ones = 0;
    int threes = 0;

    for (auto [a, b] : views::zip(adapters, adapters | views::drop(1))) {
        auto diff = b - a;
        switch (diff) {
        case 1:
            ++ones;
            break;
        case 3:
            ++threes;
            break;
        }
    }

    fmt::print("part 1: {}\n", ones * threes);

    return 0;
}
