#include <cctype>
#include <charconv>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

auto numbers(std::string_view line) {

    return views::filter(views::enumerate(line), [](const auto &p) { return std::isdigit(p.second); }) |
           views::chunk_by([](const auto &l, const auto &r) { return l.first + 1 == r.first; }) |
           views::transform([](auto &&rng) {
               auto it = ranges::begin(rng);
               auto start = (*it).first;
               auto len = ranges::distance(rng);
               return std::make_pair(start, len);
           });
}

std::vector<std::vector<int>> parse_numbers(const std::vector<std::string> &schematic) {
    std::vector<std::vector<int>> res;
    std::string buf;
    for (auto [row, line] : views::enumerate(schematic)) {
        auto &out = res.emplace_back(line.size(), 0);
        for (auto [start, len] : numbers(line)) {
            auto str = line.substr(start, len);
            auto i = 0;
            std::from_chars(str.data(), str.data() + str.size(), i);
            ranges::fill_n(out.begin() + start, len, i);
        }
    }

    return res;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::vector<std::string> schematic;

    {
        std::ifstream in{argv[1]};
        schematic = ranges::getlines(in) | ranges::to<std::vector>;
    }

    auto numbers = parse_numbers(schematic);

    int sum = 0;

    std::vector<int> buf;
    for (auto [row, line] : views::enumerate(schematic)) {
        for (auto [col, c] : views::enumerate(line)) {
            if (c == '.' || std::isdigit(c)) {
                continue;
            }

            buf.clear();

            for (auto y : views::ints(row == 0 ? 0 : row - 1, std::min(schematic.size(), row + 1) + 1)) {
                for (auto x : views::ints(col == 0 ? 0 : col - 1, std::min(line.size(), col + 1) + 1)) {
                    buf.push_back(numbers[y][x]);
                }
            }

            ranges::sort(buf);

            sum += ranges::accumulate(views::unique(buf), 0);
        }
    }

    fmt::print("part 1: {}\n", sum);

    uint64_t ratios = 0;
    for (auto [row, line] : views::enumerate(schematic)) {
        for (auto [col, c] : views::enumerate(line)) {
            if (c != '*') {
                continue;
            }

            buf.clear();

            for (auto y : views::ints(row == 0 ? 0 : row - 1, std::min(schematic.size(), row + 1) + 1)) {
                for (auto x : views::ints(col == 0 ? 0 : col - 1, std::min(line.size(), col + 1) + 1)) {
                    buf.push_back(numbers[y][x]);
                }
            }

            ranges::actions::sort(buf);
            ranges::actions::unique(buf);

            if (buf.size() == 3) {
                ratios += buf[1] * buf[2];
            }
        }
    }

    fmt::print("part 2: {}\n", ratios);

    return 0;
}
