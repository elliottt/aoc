#include <fmt/core.h>
#include <iterator>
#include <range/v3/all.hpp>
#include "md5.h"

namespace views = ranges::views;

std::string md5(std::string input) {
    MD5 hash;
    hash.add(input.data(), input.size());
    return hash.getHash();
}

int leading_zeros(std::string digest) {
    return ranges::count(digest | views::take_while([](auto c) { return c == '0'; }), '0');
}

int main(int argc, char **argv) {
    auto res = views::iota(1) | views::transform([](auto i) -> std::pair<int, int> {
                   auto digest = md5("iwrupvqb" + std::to_string(i));
                   return {i, leading_zeros(digest)};
               }) |
               views::drop_while([](auto p) { return p.second != 5; }) | views::take(1) |
               ranges::to<std::vector<std::pair<int, int>>>();

    fmt::print("part-1: {}\n", res.front().first);

    return 0;
}
