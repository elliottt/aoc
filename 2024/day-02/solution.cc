#include <charconv>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

using Level = std::vector<int>;

std::vector<int> compute_diff(Level &lev) {
    return views::zip_with([](auto a, auto b) { return a - b; }, lev, views::drop(lev, 1)) | ranges::to<std::vector>();
}

bool is_safe(Level &lev) {
    auto diffs = compute_diff(lev);

    return ranges::all_of(diffs, [](auto x) { return x > 0 && x <= 3; }) ||
           ranges::all_of(diffs, [](auto x) { return x < 0 && x >= -3; });
}

// Really unsatisfying solution.
bool could_dampen(Level &lev) {
    auto diffs = compute_diff(lev);
    auto ascending = ranges::count_if(diffs, [](auto x) { return x >= 0; }) > (diffs.size() / 2);

    size_t offset;
    if (ascending) {
        auto it = ranges::find_if(diffs, [](auto x) { return x <= 0 || x > 3; });
        offset = std::distance(diffs.begin(), it);
    } else {
        auto it = ranges::find_if(diffs, [](auto x) { return x >= 0 || x < -3; });
        offset = std::distance(diffs.begin(), it);
    }

    auto copy = lev;
    copy.erase(copy.begin() + offset);

    if (is_safe(copy)) {
        return true;
    }

    offset++;
    if (offset == lev.size()) {
        return false;
    }

    copy = lev;
    copy.erase(copy.begin() + offset);

    return is_safe(copy);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::vector<Level> report;

    {
        std::ifstream in{argv[1]};

        for (auto &line : ranges::getlines(in)) {
            report.push_back(
                line | views::split(' ') | views::transform([](auto &&rng) -> int {
                    int ret;
                    auto start = &*rng.begin();
                    auto size = ranges::distance(rng);
                    std::from_chars(start, start + size, ret);
                    return ret;
                }) |
                ranges::to<std::vector>());
        }
    }

    fmt::print("part 1: {}\n", ranges::count_if(report, is_safe));
    fmt::print("part 2: {}\n", ranges::count_if(report, [](auto &lev) { return is_safe(lev) || could_dampen(lev); }));

    return 0;
}
