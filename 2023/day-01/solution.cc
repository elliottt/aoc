#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace views = ranges::views;

void numbers(std::string_view str, bool allow_words, std::vector<int> &res) {
    res.clear();

    for (auto [ix, c] : views::enumerate(str)) {
        if (std::isdigit(c)) {
            res.push_back(c - '0');
            continue;
        }

        if (!allow_words) {
            continue;
        }

        auto rest = str.substr(ix);

        switch (c) {
        case 'o':
            if (rest.starts_with("one")) {
                res.push_back(1);
            }
            break;

        case 't':
            if (rest.starts_with("two")) {
                res.push_back(2);
            } else if (rest.starts_with("three")) {
                res.push_back(3);
            }
            break;

        case 'f':
            if (rest.starts_with("four")) {
                res.push_back(4);
            } else if (rest.starts_with("five")) {
                res.push_back(5);
            }
            break;

        case 's':
            if (rest.starts_with("six")) {
                res.push_back(6);
            } else if (rest.starts_with("seven")) {
                res.push_back(7);
            }
            break;

        case 'e':
            if (rest.starts_with("eight")) {
                res.push_back(8);
            }
            break;

        case 'n':
            if (rest.starts_with("nine")) {
                res.push_back(9);
            }
            break;

        default:
            break;
        }
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    {
        std::ifstream in{argv[1]};

        std::vector<int> buf;
        auto res = ranges::accumulate(
            ranges::getlines(in) | views::transform([&buf](auto &line) {
                numbers(line, false, buf);
                auto res = buf.front() * 10 + buf.back();
                return res;
            }),
            0L);

        fmt::print("part 1: {}\n", res);
    }

    {
        std::ifstream in{argv[1]};

        std::vector<int> buf;
        auto res = ranges::accumulate(
            ranges::getlines(in) | views::transform([&buf](auto &line) {
                numbers(line, true, buf);
                auto res = buf.front() * 10 + buf.back();
                return res;
            }),
            0L);

        fmt::print("part 2: {}\n", res);
    }

    return 0;
}
