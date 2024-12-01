#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::vector<int> col1;
    std::vector<int> col2;

    {
        std::ifstream in{argv[1]};

        for (auto &line : ranges::getlines(in)) {
            auto end = line.find("   ");
            col1.push_back(std::stoi(line.substr(0, end)));
            col2.push_back(std::stoi(line.substr(end + 3)));
        }
    }

    ranges::sort(col1);
    ranges::sort(col2);

    fmt::print(
        "part 1: {}\n",
        ranges::accumulate(
            views::zip_with([](auto a, auto b) { return std::max(a, b) - std::min(a, b); }, col1, col2),
            0));

    auto right = col2.begin();
    fmt::print(
        "part 2: {}\n",
        ranges::accumulate(
            views::chunk_by(col1, std::equal_to{}) | views::transform([&right, &col2](auto left) -> int {
                // Figure out how many of the same val are present
                auto val = *left.begin();
                auto left_count = ranges::size(left);

                right = std::lower_bound(right, col2.end(), val);
                if (right == col2.end()) {
                    return 0;
                }

                if (*right != val) {
                    return 0;
                }

                auto end = std::find_if(right, col2.end(), [val](auto x) { return x != val; });
                auto right_count = std::distance(right, end);
                right = end;

                return left_count * (val * right_count);
            }),
            0));

    return 0;
}
