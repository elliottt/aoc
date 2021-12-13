#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>
#include <optional>

namespace views = ranges::views;

struct result {
    enum type {
        Valid,
        Incomplete,
        Corrupted,
    };

    type ty{Valid};
    size_t error_pos{std::string::npos};
    std::string closing;
};

// Returns the closing token if this is an opening token.
std::optional<char> is_open_token(char c) {
    switch (c) {
    case '(':
        return ')';
    case '[':
        return ']';
    case '{':
        return '}';
    case '<':
        return '>';
    default:
        return std::nullopt;
    }
}

result parse(const std::string &line) {
    std::string stack;
    result res;

    for (auto [i, c] : views::enumerate(line)) {
        if (auto closing = is_open_token(c)) {
            stack.push_back(*closing);
        } else {
            if (c != stack.back()) {
                res.ty = result::Corrupted;
                if (res.error_pos == std::string::npos) {
                    res.error_pos = i;
                }
            }
            stack.pop_back();
        }
    }

    if (res.ty == result::Valid && !stack.empty()) {
        res.ty = result::Incomplete;
        res.closing = stack;
    }

    return res;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::vector<std::string> lines;

    {
        std::ifstream in{argv[1]};
        ranges::copy(ranges::getlines(in), ranges::back_inserter(lines));
    }

    auto results = views::transform(lines, parse) | ranges::to<std::vector<result>>;

    int score = 0;
    for (const auto &[ix, res] : views::enumerate(results)) {
        if (res.ty != result::Corrupted) {
            continue;
        }

        switch (lines[ix][res.error_pos]) {
            case ')':
                score += 3;
                break;
            case ']':
                score += 57;
                break;
            case '}':
                score += 1197;
                break;
            case '>':
                score += 25137;
                break;
        }
    }

    fmt::print("part 1: {}\n", score);

    std::vector<uint64_t> scores;
    for (const auto &[ix, res] : views::enumerate(results)) {
        if (res.ty != result::Incomplete) {
            continue;
        }

        uint64_t score = 0;
        for (auto c : views::reverse(res.closing)) {
            score = score * 5;
            switch (c) {
                case ')':
                    score += 1;
                    break;
                case ']':
                    score += 2;
                    break;
                case '}':
                    score += 3;
                    break;
                case '>':
                    score += 4;
                    break;
            }
        }

        scores.push_back(score);
    }

    ranges::sort(scores);

    auto middle = (scores.size() >> 1);

    fmt::print("part 2: {}\n", scores[middle]);

    return 0;
}
