#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <regex>

using namespace ranges;
using namespace std;

struct reindeer {
    string name;
    int speed;
    int duration;
    int rest;

    static reindeer parse(const string &line) {
        auto words = line | views::tokenize(regex{"[\\w]+"}) | to<vector<string>>();
        return reindeer{words[0], stoi(words[3]), stoi(words[7]), stoi(words[14])};
    }

    void print() const {
        fmt::print("{} travels at {}km/s for {}s and rests for {}s\n", name, speed,
                   duration, rest);
    }
};

struct position {
    bool racing;
    int remaining;
    int dist;

    static position from_reindeer(reindeer &racer) {
        return position{true, racer.duration, 0};
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

void step(const vector<reindeer> &racers, vector<position> &state) {
    for (auto const &[racer, pos] : views::zip(racers, state)) {
        pos.step(racer);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    vector<reindeer> racers;
    vector<position> state;

    {
        ifstream in{argv[1]};
        in >> noskipws;
        for (auto const &line : getlines(in)) {
            racers.emplace_back(reindeer::parse(line));
            state.emplace_back(position::from_reindeer(racers.back()));
        }
    }

    for (int i = 0; i < 2503; i++) {
        step(racers, state);
    }

    fmt::print("part 1: {}\n", ranges::max_element(state, {}, &position::dist)->dist);

    return 0;
}
