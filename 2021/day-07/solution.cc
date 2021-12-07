#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <utility>
#include <vector>

namespace views = ranges::views;

int min_fuel(const std::vector<int> &crabs, std::function<int(int, int)> fuel_needed) {
    auto positions = views::iota(crabs.front(), crabs.back() + 1);
    return ranges::min(
               positions | views::transform([&crabs, &fuel_needed](auto a) {
                   auto candidate = ranges::accumulate(
                       crabs | views::transform([a, &fuel_needed](auto b) { return fuel_needed(a, b); }),
                       0);
                   return std::make_pair(a, candidate);
               }),
               ranges::less{},
               [](auto p) { return p.second; })
        .second;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    std::vector<int> crabs;
    {
        std::ifstream in{argv[1]};
        std::string line;
        std::getline(in, line);
        ranges::copy(
            line | views::split(',') | views::transform([](auto &&rng) {
                std::string str(&*rng.begin(), ranges::distance(rng));
                return std::stoi(str);
            }),
            ranges::back_inserter(crabs));

        ranges::sort(crabs);
    }

    fmt::print("part 1: {}\n", min_fuel(crabs, [](auto a, auto b) { return std::abs(a - b); }));
    fmt::print("part 2: {}\n", min_fuel(crabs, [](auto a, auto b) {
                   auto diff = std::abs(a - b);
                   auto sum = (diff * (diff + 1)) / 2;
                   return sum;
               }));

    return 0;
}
