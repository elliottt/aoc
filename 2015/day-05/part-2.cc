#include <algorithm>
#include <fmt/core.h>
#include <fstream>
#include <iterator>
#include <range/v3/all.hpp>
#include <string>

using namespace std;

// substring occurrences like `...ab...ab...`
bool contains_double_repeat(string str) {
    using namespace ranges;

    // indices for possible two-letter sequence starts
    auto ixs = views::ints(0, static_cast<int>(str.size()) - 2);

    auto has_substr_from = [&str](auto ix) {
        auto substr = str.substr(ix, 2);
        return !ranges::empty(ranges::search(str | views::drop(ix + 2), substr));
    };

    return ranges::find_if(ixs, has_substr_from) != ranges::end(ixs);
}

// substring occurrences like `...xyx...`
bool contains_one_letter_repeat(string str) {
    using namespace ranges;

    auto ixs = views::ints(1, static_cast<int>(str.size()) - 1);

    auto has_one_letter_repeat = [&str](auto ix) { return str[ix - 1] == str[ix + 1]; };

    return ranges::find_if(ixs, has_one_letter_repeat) != ranges::end(ixs);
}

bool is_nice(string str) {
    return contains_double_repeat(str) && contains_one_letter_repeat(str);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    ifstream in{argv[1]};
    fmt::print("part 2: {}\n", ranges::count_if(ranges::istream<string>(in), is_nice));

    return 0;
}
