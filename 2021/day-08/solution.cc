#include <bit>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

struct signal {
    std::vector<std::string> input;
    std::vector<std::string> output;
};

auto parse(const std::string input) {
    return input | views::split(' ') | views::transform([](auto &&rng) {
               auto str = ranges::to<std::string>(rng);
               ranges::sort(str);
               return str;
           }) |
           ranges::to<std::vector<std::string>>;
}

bool is_unique(const std::string &str) {
    return str.size() == 2 || str.size() == 4 || str.size() == 3 || str.size() == 7;
}

bool merge_to_eight(const std::string &a, const std::string &b) {
    const std::string eight = "abcdefg";
    return ranges::all_of(eight, [&a, &b](auto c) { return ranges::contains(a, c) || ranges::contains(b, c); });
}

// experimentally, every line has the digits 1, 4, 7, and 8 present
int decode(const signal &signal) {

    std::vector<std::string> digits(10, "");
    std::vector<std::string> zero_six_nine;
    std::vector<std::string> two_three_five;

    for (auto &str : views::concat(signal.input, signal.output)) {
        if (str.size() == 2) {
            digits[1] = str;
        } else if (str.size() == 4) {
            digits[4] = str;
        } else if (str.size() == 3) {
            digits[7] = str;
        } else if (str.size() == 7) {
            digits[8] = str;
        } else if (str.size() == 5) {
            two_three_five.push_back(str);
        } else if (str.size() == 6) {
            zero_six_nine.push_back(str);
        }
    }

    ranges::unique(zero_six_nine);
    ranges::unique(two_three_five);

    auto find_candidate = [&digits](size_t ix, auto &candidates, size_t other) {
        auto digit = ranges::find_if(candidates, [&digits, other](auto &candidate) {
            return merge_to_eight(candidate, digits[other]);
        });
        if (digit != ranges::end(candidates)) {
            digits[ix] = *digit;
            candidates.erase(digit);
        }
    };

    find_candidate(6, zero_six_nine, 1);
    find_candidate(0, zero_six_nine, 4);
    if (!zero_six_nine.empty()) {
        digits[9] = zero_six_nine.front();
    }

    find_candidate(2, two_three_five, 4);

    auto three = ranges::find_if(two_three_five, [&digits](auto &str) {
        return ranges::all_of(digits[7], [&str](char c) { return ranges::contains(str, c); });
    });
    if (three != ranges::end(two_three_five)) {
        digits[3] = *three;
        two_three_five.erase(three);
    }

    if (!two_three_five.empty()) {
        digits[5] = two_three_five.front();
    }

    return ranges::accumulate(
        views::transform(
            signal.output,
            [&digits](auto &output) {
                auto digit = ranges::find(digits, output);
                return std::distance(digits.begin(), digit);
            }),
        0u,
        [](auto a, auto b) { return a * 10 + b; });
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::vector<signal> signals;

    {
        std::ifstream in{argv[1]};
        for (auto line : ranges::getlines(in)) {
            auto &signal = signals.emplace_back();
            auto pipe = line.find(" | ");

            signal.input = parse(line.substr(0, pipe));
            signal.output = parse(line.substr(pipe + 3));
        }
    }

    fmt::print(
        "part 1: {}\n",
        ranges::accumulate(
            views::transform(signals, [](auto &input) { return ranges::count_if(input.output, is_unique); }),
            0));

    fmt::print("part 2: {}\n", ranges::accumulate(views::transform(signals, decode), 0));

    return 0;
}
