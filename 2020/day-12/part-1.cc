#include <range/v3/all.hpp>
#include <fmt/core.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
using namespace ranges;

struct position {
    int x{0};
    int y{0};
    int dir{0};

    void turn(int val) {
        dir += (val + 360);
        dir %= 360;
    }

    void move_forward(int val) {
        switch (dir % 360) {
        case 0:
            x += val;
            break;
        case 90:
            y += val;
            break;
        case 180:
            x -= val;
            break;
        case 270:
            y -= val;
            break;
        }
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    position pos{};

    ifstream in{argv[1]};
    for (auto &line : getlines(in)) {
        auto val = stoi(line.substr(1));

        switch (line[0]) {
        case 'N':
            pos.y += val;
            break;
        case 'S':
            pos.y -= val;
            break;
        case 'E':
            pos.x += val;
            break;
        case 'W':
            pos.x -= val;
            break;
        case 'L':
            pos.turn(val);
            break;
        case 'R':
            pos.turn(-val);
            break;
        case 'F':
            pos.move_forward(val);
            break;
        }
    }

    fmt::print("part 1: {}\n", abs(pos.x) + abs(pos.y));

    return 0;
}
