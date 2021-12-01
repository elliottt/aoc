#include <fmt/core.h>
#include <range/v3/all.hpp>
#include <string>

using namespace std;
using namespace ranges;

void increment(string &input) {
    for (int digit = input.size() - 1; digit >= 0; --digit) {
        char prev = input[digit];

        input[digit] = (((prev - 'a') + 1) % 26) + 'a';

        if (prev != 'z') {
            return;
        }
    }

    input.reserve(input.size() + 1);
    input.insert(0, "a");

    return;
}

bool increasing_straight(const string &password) {
    return ranges::any_of(password | views::take(password.size() - 2) | views::enumerate, [&password](auto p) {
        auto [ix, c] = p;
        return password[ix + 1] == c + 1 && password[ix + 2] == c + 2;
    });
}

bool no_easily_mistaken(const string &password) {
    return !ranges::any_of(password, [](auto c) { return c == 'i' || c == 'o' || c == 'l'; });
}

bool double_letters(const string &password) {

    // characters that are followed by the same character again
    auto repeats = password | views::take(password.size() - 1) | views::enumerate | views::filter([&password](auto p) {
                       auto [ix, c] = p;
                       return password[ix + 1] == c;
                   }) |
                   views::transform([](auto p) { return p.second; });

    return ranges::accumulate(repeats | views::unique | views::transform([](auto _) { return 1; }), 0) > 1;
}

bool valid_password(const string &password) {
    return increasing_straight(password) && no_easily_mistaken(password) && double_letters(password);
}

string next_password(const string &password) {
    string result = password;
    for (increment(result); !valid_password(result); increment(result)) {
    }
    return result;
}

int main(int argc, char **argv) {
    string input{"hepxcrrq"};
    input = next_password(input);
    fmt::print("part 2: {}\n", next_password(input));

    return 0;
}
