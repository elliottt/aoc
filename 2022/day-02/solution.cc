#include <cassert>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

struct Round {
    char them = 0;
    char us = 0;

    explicit Round(std::string_view line) : them{line[0]}, us{line[2]} {}
    Round(char them, char us) : them{them}, us{us} {}

    static char winner(unsigned char them) {
        return (((them - 'A') + 1) % 3) + 'X';
    }

    static char loser(unsigned char them) {
        return ((them + 3) % 3) + 'X';
    }

    static char same(unsigned char them) {
        return ((them - 'A') % 3) + 'X';
    }

    int score() const {
        auto score = this->us - 'X' + 1;

        if (Round::winner(this->them) == this->us) {
            score += 6;
        } else if (Round::same(this->them) == this->us) {
            score += 3;
        }

        return score;
    }

    int choice() const {
        auto score = 0;

        switch (this->us) {
        case 'X':
            score = Round{this->them, Round::loser(this->them)}.score();
            break;

        case 'Y':
            score = Round{this->them, Round::same(this->them)}.score();
            break;

        case 'Z':
            score = Round{this->them, Round::winner(this->them)}.score();
            break;
        }

        return score;
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    std::vector<Round> rounds;
    {
        std::ifstream in{argv[1]};
        rounds =
            ranges::getlines(in) | views::transform([](auto &line) { return Round(line); }) | ranges::to<std::vector>;
    }

    fmt::print("part 1: {}\n", ranges::accumulate(views::transform(rounds, &Round::score), 0));
    fmt::print("part 2: {}\n", ranges::accumulate(views::transform(rounds, &Round::choice), 0));

    return 0;
}
