#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

using namespace ranges;
using namespace std;

struct problem {
    int min;
    int max;
    char c;
    string password;

    static problem parse(const string &str) {
        int min = stoi(str);
        int max = stoi(str.substr(str.find('-') + 1));
        char c = str.substr(str.find(' ') + 1)[0];
        return {min, max, c, str.substr(str.find(':') + 2)};
    }

    bool is_valid() {
        return (password[min-1] == c) ^ (password[max-1] == c);
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    ifstream in{argv[1]};
    fmt::print("part 1: {}\n", ranges::count_if(getlines(in) |
                views::transform(problem::parse), &problem::is_valid));
}
