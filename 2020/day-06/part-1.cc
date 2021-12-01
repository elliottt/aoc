#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>

using std::ifstream, std::string;
using namespace ranges;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    ifstream in{argv[1]};

    auto total = ranges::accumulate(
        getlines(in) | views::split("") | views::transform([](auto rng) {
            string all = rng | views::join | to<string>() | actions::sort | actions::unique;
            return all.size();
        }),
        0);

    fmt::print("part 1: {}\n", total);

    return 0;
}
