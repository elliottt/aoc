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

auto visit_houses(string directions) {
    using namespace ranges;
    point acc{0, 0};
    return views::concat(views::single(acc),
                         directions | views::transform([&acc](char direction) {
                             auto res = ::next(acc, direction);
                             acc = res;
                             return res;
                         })) |
           ranges::to<vector<point>>();
}

auto total_visited(string directions) {
    using namespace ranges;

    auto is_even = [](auto p) { return p.first % 2 == 0; };

    auto santa = directions | views::enumerate | views::filter(is_even) |
                 views::transform([](auto p) { return p.second; }) |
                 ranges::to<string>();

    auto robot = directions | views::enumerate | views::remove_if(is_even) |
                 views::transform([](auto p) { return p.second; }) |
                 ranges::to<string>();

    auto santa_visited = visit_houses(santa);
    auto robot_visited = visit_houses(robot);
    auto all_houses = views::concat(santa_visited, robot_visited) |
                      ranges::to<vector<point>>() |
                      actions::sort(&point::operator<);

    return ranges::accumulate(
        all_houses | views::group_by(&point::operator==) |
            views::transform([](auto group) { return 1; }),
        0);
}

int main(int argc, char **argv) {
    using namespace ranges;

    if (argc != 2) {
        return 1;
    }

    string directions;

    {
        ifstream in{argv[1]};
        std::copy(istream_iterator<char>{in}, istream_iterator<char>{},
                  std::back_inserter(directions));
    }

    fmt::print("part 2: {}\n", total_visited(directions));

    return 0;
}
