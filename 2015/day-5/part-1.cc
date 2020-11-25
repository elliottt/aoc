#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <iterator>
#include <fmt/core.h>
#include <range/v3/all.hpp>

using namespace std;

bool is_vowel(char c) {
    static const string vowels{"aeiou"};
    return ranges::find(vowels, c) != ranges::end(vowels);
}

bool contains_repeat(string str) {
    if (str.empty()) {
        return false;
    }

    char prev = str[0];
    return ranges::find_if(str | ranges::views::drop(1), [&prev](char c) {
                auto found = c == prev;
                prev = c;
                return found;
            }) != ranges::end(str);
}

bool is_nice(string str) {
    return ranges::count_if(str, is_vowel) >= 3 &&
            contains_repeat(str) &&
            ranges::empty(ranges::search(str, "ab"s)) &&
            ranges::empty(ranges::search(str, "cd"s)) &&
            ranges::empty(ranges::search(str, "pq"s)) &&
            ranges::empty(ranges::search(str, "xy"s));
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    vector<string> input;
    {
        ifstream in{argv[1]};
        copy(istream_iterator<string>{in}, istream_iterator<string>{}, back_inserter(input));
    }

    fmt::print("part 1: {}\n", ranges::count_if(input, is_nice));

    return 0;
}
