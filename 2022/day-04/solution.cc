#include <cassert>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <utility>
#include <vector>

namespace views = ranges::views;

struct Interval {
    int low;
    int high;

    Interval(int low, int high) : low{low}, high{high} {}

    static Interval parse(const std::string &str) {
        auto sep = str.find('-');
        assert(sep != str.npos);

        return Interval{std::stoi(str.substr(0, sep)), std::stoi(str.substr(sep + 1))};
    }

    bool contains(int val) const {
        return this->low <= val && val <= this->high;
    }

    bool contains(Interval &other) const {
        return this->contains(other.low) && this->contains(other.high);
    }

    bool overlaps(Interval &other) const {
        return this->contains(other.low) || this->contains(other.high);
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::vector<std::pair<Interval, Interval>> pairs;
    {
        std::ifstream in{argv[1]};
        pairs = ranges::getlines(in) | views::transform([](const auto &line) {
                    auto sep = line.find(',');
                    assert(sep != line.npos);
                    auto first = Interval::parse(line.substr(0, sep));
                    auto second = Interval::parse(line.substr(sep + 1));
                    return std::make_pair(first, second);
                }) |
                ranges::to<std::vector>;
    }

    fmt::print("part 1: {}\n", ranges::count_if(pairs, [](auto &p) {
                   return p.first.contains(p.second) || p.second.contains(p.first);
               }));

    fmt::print("part 2: {}\n", ranges::count_if(pairs, [](auto &p) {
                   return p.first.overlaps(p.second) || p.second.overlaps(p.first);
               }));

    return 0;
}
