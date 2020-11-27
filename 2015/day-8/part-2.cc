#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <regex>
#include <string>

using namespace std;

int count_encoded_characters(const string &line) {
    // trim off the newline
    auto code = line.size() - 1;

    // the encoded format adds two double-quote characters
    auto encoded = 2;

    // start after the first double-quote
    for (auto i = 0; i < code; ++i, ++encoded) {
        switch (line[i]) {
        case '\\':
        case '"':
            ++encoded;
            break;
        }
    }

    return encoded - code;
}

int test(string str) {
    auto enc = count_encoded_characters(str + "\n");
    fmt::print("{} = {}\n", str, enc);
    return enc;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    string input;
    {
        ifstream in{argv[1]};
        in >> noskipws;
        ranges::copy(ranges::istream<char>(in), ranges::back_inserter(input));
    }

    auto total = ranges::accumulate(
        input | ranges::views::tokenize(regex{"[^\n]+\n"}) |
            ranges::views::transform(count_encoded_characters),
        0);

    fmt::print("part 2: {}\n", total);

    return 0;
}
