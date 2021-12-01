#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

using std::ifstream, std::string, std::vector, std::pair, std::regex;
using namespace ranges;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    int leave{0};
    vector<pair<int, int>> busses{};

    {
        ifstream in{argv[1]};

        string line;
        getline(in, line);
        leave = stoi(line);

        getline(in, line);
        ranges::copy(
            line | views::tokenize(regex{"[[:digit:]]+"}) | views::transform([](auto const &str) -> pair<int, int> {
                return {stoi(str), 0};
            }),
            ranges::back_inserter(busses));
    }

    while (ranges::all_of(busses, [leave](auto &bus) { return bus.second < leave; })) {
        for (auto &bus : busses) {
            bus.second += bus.first;
        }
    }

    auto [bus, time] = *ranges::min_element(busses, {}, [leave](auto &bus) {
        if (bus.second < leave) {
            return std::numeric_limits<int>::max();
        } else {
            return bus.second - leave;
        }
    });

    fmt::print("part 1: {}\n", bus * (time - leave));

    return 0;
}
