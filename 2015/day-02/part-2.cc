#include <algorithm>
#include <fmt/core.h>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include <range/v3/all.hpp>

int ribbon_required(std::string line) {
    auto a = line.find('x');
    auto b = line.find('x', a + 1);

    auto l = stoi(line.substr(0, a));
    auto w = stoi(line.substr(a + 1, b - a));
    auto h = stoi(line.substr(b + 1, std::string::npos));

    auto wrap = 2 * std::min({l + w, w + h, h + l});
    auto bow = l * w * h;

    return wrap + bow;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    std::vector<std::string> input;
    {
        std::ifstream in{argv[1]};
        ranges::copy(ranges::getlines(in), ranges::back_inserter(input));
    }

    fmt::print("part 2: {}\n", ranges::accumulate(input | ranges::views::transform(ribbon_required), 0));

    return 0;
}
