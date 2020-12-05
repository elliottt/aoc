#include <cctype>
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

const vector<string> required{"byr", "iyr", "eyr", "hgt",
                              "hcl", "ecl", "pid", "cid"};

const string valid_hcl{"0123456789abcdef"};

const vector<string> valid_ecl{"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

bool valid_year(const string &str, int lower, int upper) {
    if (str.size() != 4) {
        return false;
    }

    if (ranges::any_of(str, [](auto c) { return !isdigit(c); })) {
        return false;
    }

    auto val = stoi(str);
    return lower <= val && val <= upper;
}

bool check_passport(const passport &p) {
    auto missing = ranges::count_if(
        required, [&p](auto &field) { return p.find(field) == p.end(); });

    if (missing > 1) {
        return false;
    }

    if (missing == 1 && p.find("cid") != p.end()) {
        return false;
    }

    auto &byr = p.find("byr")->second;
    if (!valid_year(byr, 1920, 2002)) {
        return false;
    }

    auto &iyr = p.find("iyr")->second;
    if (!valid_year(iyr, 2010, 2020)) {
        return false;
    }

    auto &eyr = p.find("eyr")->second;
    if (!valid_year(eyr, 2020, 2030)) {
        return false;
    }

    auto &hgt_field = p.find("hgt")->second;
    auto hgt = stoi(hgt_field);
    if (hgt_field.rfind("cm") == hgt_field.size() - 2) {
        if (hgt < 150 || hgt > 193) {
            return false;
        }
    } else if (hgt_field.rfind("in") == hgt_field.size() - 2) {
        if (hgt < 59 || hgt > 76) {
            return false;
        }
    } else {
        return false;
    }

    auto hcl = p.find("hcl")->second;
    if (hcl.size() != 7 || hcl[0] != '#' ||
        ranges::any_of(hcl | views::drop(1), [](auto c) {
            return ranges::find(valid_hcl, c) == valid_hcl.end();
        })) {
        return false;
    }

    auto ecl = p.find("ecl")->second;
    if (ranges::find(valid_ecl, ecl) == valid_ecl.end()) {
        return false;
    }

    auto pid = p.find("pid")->second;
    if (pid.size() != 9 ||
        ranges::any_of(pid, [](auto c) { return !isdigit(c); })) {
        return false;
    }

    return true;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    ifstream in{argv[1]};

    passport current;
    int valid{0};

    valid = ranges::count_if(
        getlines(in) | views::split("") | views::transform([](auto lines) {
            passport p{};
            ranges::for_each(lines,
                             [&p](auto &line) { extend_passport(p, line); });
            return p;
        }),
        check_passport);

    fmt::print("part 2: {}\n", valid);

    return 0;
}
