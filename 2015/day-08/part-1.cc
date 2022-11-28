#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <regex>
#include <string>

int count_characters(const std::string &line) {
    auto in_memory = 0;

    // start after the first double-quote
    auto i = 1;
    for (; i < line.size() - 2; ++i, ++in_memory) {
        if (line[i] == '\\') {
            switch (line[i + 1]) {
            case '\\':
            case '"':
                i += 1;
                break;
            case 'x':
                i += 3;
                break;
            }
        }
    }

    // add the last double-quote in
    auto total = i + 1;

    return total - in_memory;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    std::string input;
    {
        std::ifstream in{argv[1]};
        in >> std::noskipws;
        ranges::copy(ranges::istream<char>(in), ranges::back_inserter(input));
    }

    auto total = ranges::accumulate(
        input | ranges::views::tokenize(std::regex{"[^\n]+\n"}) | ranges::views::transform(count_characters),
        0);

    fmt::print("part 1: {}\n", total);

    return 0;
}
