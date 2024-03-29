#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <regex>

namespace views = ranges::views;

struct reindeer {
    std::string name;
    int speed;
    int duration;
    int rest;

    static reindeer parse(const std::string &line) {
        auto words = line | views::tokenize(std::regex{"[\\w]+"}) | ranges::to<std::vector<std::string>>();
        return reindeer{words[0], stoi(words[3]), stoi(words[7]), stoi(words[14])};
    }

    void print() const {
        fmt::print("{} travels at {}km/s for {}s and rests for {}s\n", name, speed, duration, rest);
    }
};

struct position {
    bool racing;
    int remaining;
    int dist;
    int score;

    static position from_reindeer(reindeer &racer) {
        return position{true, racer.duration, 0, 0};
    }

    void step(const reindeer &racer) {
        if (remaining <= 0) {
            racing = !racing;
            if (racing) {
                remaining = racer.duration;
            } else {
                remaining = racer.rest;
            }
        }

        if (racing) {
            dist += racer.speed;
        }

        remaining--;
    }
};

void step(const std::vector<reindeer> &racers, std::vector<position> &state) {
    for (auto const &[racer, pos] : views::zip(racers, state)) {
        pos.step(racer);
    }

    ranges::max_element(state, {}, &position::dist)->score += 1;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    std::vector<reindeer> racers;
    std::vector<position> state;

    {
        std::ifstream in{argv[1]};
        in >> std::noskipws;
        for (auto const &line : ranges::getlines(in)) {
            racers.emplace_back(reindeer::parse(line));
            state.emplace_back(position::from_reindeer(racers.back()));
        }
    }

    for (int i = 0; i < 2503; i++) {
        step(racers, state);
    }

    fmt::print("part 2: {}\n", ranges::max_element(state, {}, &position::score)->score);

    return 0;
}
