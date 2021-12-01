#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>

using std::ifstream, std::vector;
using namespace ranges;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    vector<long> numbers{};

    {
        ifstream in{argv[1]};
        numbers = getlines(in) | views::transform([](auto &str) { return stol(str); }) | to<vector>();
    }

    long invalid{0};
    for (auto const &p : numbers | views::enumerate | views::drop(25)) {
        auto start = p.first - 25;
        auto window = numbers | views::drop(start) | views::take(25);

        auto pairs = views::cartesian_product(window, window);
        auto res = ranges::find_if(pairs, [&p](auto const &c) {
            auto [a, b] = c;
            return a + b == p.second;
        });

        if (res == ranges::end(pairs)) {
            invalid = p.second;
            break;
        }
    }

    int size = numbers.size();
    for (int start : views::iota(0, size - 2)) {
        for (auto len : views::ints(2, size - start)) {
            auto rng = numbers | views::drop(start) | views::take(len);
            long res = ranges::accumulate(rng, 0);
            if (res == invalid) {
                fmt::print("part 2: {}\n", ranges::min(rng) + ranges::max(rng));
                return 0;
            }
        }
    }

    return 0;
}
