#include <fmt/core.h>
#include <range/v3/all.hpp>
#include <string>

using namespace std;

string look_and_say(const string &input) {
    using namespace ranges;

    // This is a bit gross: since the string that stores the length of the
    // string would only live for the duration of the lambda call in
    // `transform`, the data needs to be persisted to allow the concat view to
    // execute. The solution is to make a string that can be used by the closure
    // as storage space for the temporary string used to store the length of the
    // sequence. This relies on the range being lazy.
    string len;

    return input | views::group_by(ranges::equal_to{}) | views::transform([&len](auto rng) {
               len = to_string(ranges::size(rng));
               return views::concat(len, views::single(*ranges::begin(rng)));
           }) |
           views::join | ranges::to<string>();
}

int main(int argc, char **argv) {
    string input{"3113322113"};
    for (auto i = 0; i < 50; ++i) {
        input = look_and_say(input);
    }

    fmt::print("part 2: {}\n", input.size());

    return 0;
}
