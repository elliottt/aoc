#include <algorithm>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <regex>
#include <string>
#include <vector>

namespace views = ranges::views;

uint64_t population_after(std::vector<uint8_t> lanternfish, int days) {
    std::vector<uint64_t> weekly(7, 0);
    std::vector<uint64_t> future(days+10, 0);

    // seed the future additions
    for (auto i : lanternfish) {
        weekly[i+1] += 1;
    }

    // iterate over days
    uint64_t population = lanternfish.size();
    for (auto [i, d] : future | views::enumerate | views::take(days+1)) {
        auto day = i % 7;

        // these new fish would reproduce today
        weekly[day] += future[i];

        // these will spawn new fish in 8 days
        future[i+9] += weekly[day];

        population += weekly[day];
    }

    return population;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    std::vector<uint8_t> input;
    {
        std::ifstream in{argv[1]};
        std::string line;
        std::getline(in, line);
        ranges::copy(
            line | views::split(',') | views::transform([](auto &&rng) {
                std::string str(&*rng.begin(), ranges::distance(rng));
                return std::stoi(str);
            }),
            ranges::back_inserter(input));
    }

    fmt::print("part 1: {}\n", population_after(input, 80));
    fmt::print("part 2: {}\n", population_after(input, 256));

    return 0;
}
