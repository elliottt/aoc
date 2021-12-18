#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

struct Pos {
    int x = 0;
    int y = 0;

    static Pos forward(int x) {
        return Pos{x, 0};
    }

    static Pos down(int y) {
        return Pos{0, y};
    }

    static Pos up(int y) {
        return Pos{0, -y};
    }

    Pos operator+(const Pos &other) const {
        return Pos{this->x + other.x, this->y + other.y};
    }
};

struct WithAim {
    Pos pos;
    int aim = 0;

    WithAim operator+(const Pos &other) const {
        WithAim res{this->pos, this->aim};
        if (other.x == 0) {
            res.aim += other.y;
        } else {
            res.pos.x += other.x;
            res.pos.y += other.x * res.aim;
        }
        return res;
    }
};

Pos parse_line(const std::string &line) {
    if (line.find("forward ") == 0) {
        return Pos{std::stoi(line.substr(8)), 0};
    }

    if (line.find("down ") == 0) {
        return Pos::down(std::stoi(line.substr(5)));
    }

    if (line.find("up ") == 0) {
        return Pos::up(std::stoi(line.substr(3)));
    }

    throw std::logic_error("unexpected line format");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    std::vector<Pos> deltas;

    {
        std::ifstream in{argv[1]};
        ranges::copy(
            ranges::getlines(in) | views::transform([](auto line) { return parse_line(line); }),
            ranges::back_inserter(deltas));
    }

    auto pos = ranges::accumulate(deltas, Pos{});
    fmt::print("part 1: {}\n", pos.x * pos.y);

    auto with_aim = ranges::accumulate(deltas, WithAim{});
    fmt::print("part 2: {}\n", with_aim.pos.x * with_aim.pos.y);

    return 0;
}
