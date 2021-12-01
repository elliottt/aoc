#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

using std::ifstream, std::string, std::vector, std::map;
using namespace ranges;

struct info {
    int turn_1{0}; // the previous time it was spoken
    int turn_2{0}; // the time before that

    info() : turn_1{0}, turn_2{0} {}

    explicit info(int turn) : turn_1{turn}, turn_2{0} {}

    void push_turn(int turn) {
        turn_2 = turn_1;
        turn_1 = turn;
    }

    int diff() const {
        return turn_1 - turn_2;
    }

    bool repeated() const {
        return turn_2 != 0;
    }
};

int main(int argc, char **argv) {

    vector<int> input{12, 20, 0, 6, 1, 17, 7};

    // a mapping from input to the last turn it was seen on
    map<int, info> history{};
    for (auto [ix, val] : input | views::enumerate) {
        history.emplace(val, info(ix + 1));
    }

    auto previous = input.back();
    for (auto prev_turn : views::iota(static_cast<int>(input.size()), 2020)) {
        auto turn = prev_turn + 1;

        int val{0};
        auto &last = history[previous];

        if (last.repeated()) {
            val = last.diff();
        }

        previous = val;

        auto it = history.find(val);
        if (it == history.end()) {
            history.emplace(val, info{turn});
        } else {
            it->second.push_turn(turn);
        }
    }

    fmt::print("part 1: {}\n", previous);

    return 0;
}
