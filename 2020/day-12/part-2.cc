#include <range/v3/all.hpp>
#include <fmt/core.h>
#include <fstream>
#include <vector>
#include <string>

using std::ifstream, std::string, std::vector;
using namespace ranges;

struct position {
    int x{0};
    int y{0};
    int dx{10};
    int dy{1};

    void turn(int val) {
        switch (abs(val)) {
        case 0:
            break;

        case 90:
            std::swap(dx,dy);
            if (val < 0) {
                dy = -dy;
            } else {
                dx = -dx;
            }
            break;

        case 180:
            dx = -dx;
            dy = -dy;
            break;

        case 270:
            std::swap(dx,dy);
            if (val < 0) {
                dx = -dx;
            } else {
                dy = -dy;
            }
            break;
        }
    }

    void move_forward(int val) {
        x += dx * val;
        y += dy * val;
    }

    void print() const {
        fmt::print("({},{}) <{},{}>\n", x, y, dx, dy);
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
            pos.dy += val;
            break;
        case 'S':
            pos.dy -= val;
            break;
        case 'E':
            pos.dx += val;
            break;
        case 'W':
            pos.dx -= val;
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

    fmt::print("part 2: {}\n", abs(pos.x) + abs(pos.y));

    return 0;
}
