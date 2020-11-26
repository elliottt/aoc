#include <algorithm>
#include <fmt/core.h>
#include <fstream>
#include <iterator>
#include <range/v3/all.hpp>
#include <string>

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
    return ranges::count_if(str, is_vowel) >= 3 && contains_repeat(str) &&
           ranges::empty(ranges::search(str, "ab"s)) &&
           ranges::empty(ranges::search(str, "cd"s)) &&
           ranges::empty(ranges::search(str, "pq"s)) &&
           ranges::empty(ranges::search(str, "xy"s));
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    ifstream in{argv[1]};
    fmt::print("part 1: {}\n",
               ranges::count_if(ranges::istream<string>(in), is_nice));

    return 0;
}
