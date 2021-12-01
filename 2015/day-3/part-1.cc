#include <algorithm>
#include <fmt/core.h>
#include <fstream>
#include <functional>
#include <iterator>
#include <range/v3/all.hpp>
#include <string>
#include <utility>

using namespace std;

struct point {
    int x;
    int y;

    bool operator==(const point &other) const {
        return x == other.x && y == other.y;
    }

    bool operator<(const point &other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

point next(const point &current, char direction) {
    point res{current};

    switch (direction) {
    case '^':
        res.y += 1;
        break;
    case '>':
        res.x += 1;
        break;
    case 'v':
        res.y -= 1;
        break;
    case '<':
        res.x -= 1;
        break;
    }

    return res;
}

int main(int argc, char **argv) {
    using namespace ranges;

    if (argc != 2) {
        return 1;
    }

    string directions;

    {
        ifstream in{argv[1]};
        std::copy(istream_iterator<char>{in}, istream_iterator<char>{}, std::back_inserter(directions));
    }

    point acc{0, 0};
    auto points = views::concat(views::single(acc), directions | views::transform([&acc](char direction) {
                                                        auto res = ::next(acc, direction);
                                                        acc = res;
                                                        return res;
                                                    })) |
                  ranges::to<vector<point>>();

    points |= actions::sort(&point::operator<);

    auto num_visited = ranges::accumulate(
        points | views::group_by(&point::operator==) | views::transform([](auto group) { return 1; }),
        0);

    fmt::print("part 1: {}\n", num_visited);

    return 0;
}
