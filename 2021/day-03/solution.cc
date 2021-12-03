#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

char most_common_bit(const std::vector<std::string> rows, int col) {
    auto ones = ranges::count_if(rows, [col](auto &str) { return str[col] == '1'; });
    auto zeros = ranges::count_if(rows, [col](auto &str) { return str[col] == '0'; });
    if (ones >= zeros) {
        return '1';
    } else {
        return '0';
    }
}

char flip_bit(char c) {
    if (c == '1') {
        return '0';
    } else {
        return '1';
    }
}

int from_bits(auto bits) {
    return ranges::accumulate(bits, 0, [](int acc, char c) { return (acc << 1) + (c == '1' ? 1 : 0); });
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    std::vector<std::string> lines;

    {
        std::fstream in{argv[1]};
        ranges::copy(ranges::getlines(in), ranges::back_inserter(lines));
    }

    auto num_bits = lines.front().size();

    auto gamma = views::iota(0u, num_bits) |
                 views::transform([&lines](auto col) { return most_common_bit(lines, col); }) | ranges::to<std::string>;
    auto epsilon = gamma | views::transform(flip_bit) | ranges::to<std::string>;
    fmt::print("part 1: {}\n", from_bits(gamma) * from_bits(epsilon));

    std::vector<std::string> oxygen_generator = lines;
    for (auto col : views::iota(0u, num_bits)) {
        auto bit = most_common_bit(oxygen_generator, col);
        if (oxygen_generator.size() == 1) {
            break;
        }

        oxygen_generator.erase(
            ranges::remove_if(oxygen_generator, [col, bit](auto &line) { return line[col] != bit; }),
            oxygen_generator.end());
    }

    std::vector<std::string> co2_scrubber = lines;
    for (auto col : views::iota(0u, num_bits)) {
        auto bit = flip_bit(most_common_bit(co2_scrubber, col));
        if (co2_scrubber.size() == 1) {
            break;
        }

        co2_scrubber.erase(
            ranges::remove_if(co2_scrubber, [col, bit](auto &line) { return line[col] != bit; }),
            co2_scrubber.end());
    }

    fmt::print("part 2: {}\n", from_bits(oxygen_generator.front()) * from_bits(co2_scrubber.front()));

    return 0;
}
