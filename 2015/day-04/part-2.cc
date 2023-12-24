#include "md5.h"
#include <fmt/core.h>
#include <iterator>
#include <range/v3/all.hpp>
#include <string>

namespace views = ranges::views;

std::string md5(MD5 hash, const std::string &input) {
    hash.add(input.data(), input.size());
    return hash.getHash();
}

int main(int argc, char **argv) {
    MD5 hash;
    hash.add("iwrupvqb", 8);

    std::string input;
    std::string output;
    input.reserve(20);

    for (auto i : views::iota(1)) {
        input = std::to_string(i);
        output = md5(hash, input);
        if (output.find_first_not_of('0') == 6) {
            fmt::print("part-2: {}\n", i);
            break;
        }
    }

    return 0;
}
