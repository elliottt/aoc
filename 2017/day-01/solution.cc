#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>

namespace views = ranges::views;

int matching_sum(const std::string &digits, size_t offset) {
    auto swapped = views::concat(views::drop(digits, offset), views::take(digits, offset));

    return ranges::accumulate(views::zip(digits, swapped), 0, [](auto l, auto p) {
        auto [a, b] = p;
        if (a == b) {
            return l + (a - '0');
        } else {
            return l;
        }
    });
}

int matching_halfway_sum(const std::string &digits) {
    return matching_sum(digits, digits.size() / 2);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    std::string digits;

    {
        std::fstream in{argv[1]};
        ranges::copy(ranges::istream<char>(in), ranges::back_inserter(digits));
    }

    fmt::print("part 1: {}\n", matching_sum(digits, 1));
    fmt::print("part 2: {}\n", matching_halfway_sum(digits));

    return 0;
}
