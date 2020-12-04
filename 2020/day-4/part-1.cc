#include <fmt/core.h>
#include <fmt/format.h>
#include <fstream>
#include <map>
#include <range/v3/all.hpp>
#include <regex>
#include <string>
#include <vector>

using namespace ranges;
using namespace std;

using passport = map<string, string>;

void extend_passport(passport &p, const string &line) {
    for (string m : line | views::tokenize(regex{"[#\\w:\\-]+"})) {
        auto pos = m.find(':');
        p[m.substr(0, pos)] = m.substr(pos + 1);
    }
}

vector<string> required{"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid", "cid"};

bool check_passport(const passport &p) {
    auto missing = ranges::count_if(required, [&p](auto &field) {
        return p.find(field) == p.end();
    });

    if (missing == 0) {
        return true;
    }

    if (missing == 1) {
        return p.find("cid") == p.end();
    }

    return false;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    ifstream in{argv[1]};

    passport current;
    int valid{0};

    for (auto line : views::concat(getlines(in), views::single(""))) {
        if (line.empty()) {
            if (check_passport(current)) {
                valid++;
            }
            current.clear();
            continue;
        }

        extend_passport(current, line);
    }

    fmt::print("part 1: {}\n", valid);

    return 0;
}
