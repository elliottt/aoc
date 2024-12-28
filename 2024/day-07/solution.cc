#include <charconv>
#include <cmath>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

struct Problem {
    int64_t target;
    std::vector<int64_t> operands;

    static Problem parse(std::string_view line) {
        Problem res;

        auto colon = line.find(':');
        std::from_chars(line.begin(), line.begin() + colon, res.target);
        res.operands = line.substr(colon + 2) | views::split(' ') | views::transform([](auto &&rng) -> int64_t {
                           auto start = &*rng.begin();
                           size_t len = ranges::distance(rng);
                           int64_t res;
                           std::from_chars(start, start + len, res);
                           return res;
                       }) |
                       ranges::to<std::vector>;

        return res;
    }

    bool valid(bool concatenation = false) const {
        std::vector<int64_t> current{this->target};
        std::vector<int64_t> next{};

        for (auto n : this->operands | views::reverse) {
            next.clear();
            for (auto p : current) {

                // Check for a multiplication
                if (n != 0) {
                    auto div = p / n;
                    auto rem = p % n;
                    if (rem == 0) {
                        next.push_back(div);
                    }
                }

                // Check for an addition
                next.push_back(p - n);

                // Check for concatenation
                if (concatenation) {
                    auto pow = 1L;
                    for (; n / pow > 0; pow *= 10) {
                    }

                    auto div = p / pow;
                    auto rem = p % pow;
                    if (rem == n) {
                        next.push_back(div);
                    }
                }
            }
            std::swap(current, next);
        }

        return ranges::count(current, 0);
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::vector<Problem> probs;
    {
        std::ifstream in{argv[1]};
        probs = ranges::getlines(in) | views::transform(Problem::parse) | ranges::to<std::vector>;
    }

    fmt::println(
        "part 1: {}",
        ranges::accumulate(probs | views::transform([](auto &p) { return p.valid() ? p.target : 0L; }), 0L));

    fmt::println(
        "part 2: {}",
        ranges::accumulate(probs | views::transform([](auto &p) { return p.valid(true) ? p.target : 0L; }), 0L));

    return 0;
}
