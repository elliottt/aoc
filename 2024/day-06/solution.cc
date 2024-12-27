#include <climits>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "common/pos.h"

namespace views = ranges::views;

using grid = std::vector<std::string>;

enum class PathType { Terminated, Cycle };

struct PathChecker {
    static constexpr const std::array<aoc::direction<int>, 4> dirs{
        aoc::direction<int>::north(),
        aoc::direction<int>::east(),
        aoc::direction<int>::south(),
        aoc::direction<int>::west(),
    };

    std::unordered_map<aoc::pos, std::array<bool, 4>, aoc::pos::hash> visited;

    aoc::pos start;
    aoc::bounds bounds;
    grid grid;

    PathType check(const std::optional<aoc::pos> candidate) {
        this->visited.clear();

        auto dir = 0;
        auto pos = this->start;
        while (true) {
            auto [it, _] = this->visited.insert({pos, {false, false, false, false}});
            if (it->second[dir]) {
                return PathType::Cycle;
            }

            it->second[dir] = true;

            auto next = pos.move_by(PathChecker::dirs[dir]);
            if (!this->bounds.in_bounds(next)) {
                return PathType::Terminated;
            }

            if (this->is_blocked(next, candidate)) {
                dir = PathChecker::next_dir(dir);
                continue;
            }

            pos = next;
        }
    }

    bool is_blocked(aoc::pos pos, const std::optional<aoc::pos> candidate_block) {
        return this->grid[pos.y][pos.x] == '#' || (candidate_block.has_value() && pos == *candidate_block);
    }

    static int next_dir(int dir) {
        return (dir + 1) % PathChecker::dirs.size();
    }

    static PathChecker from_input(std::ifstream in) {
        PathChecker path;

        for (auto [ix, line] : ranges::getlines(in) | views::enumerate) {
            auto it = ranges::find(line, '^');
            if (it != line.end()) {
                path.start.x = std::distance(line.begin(), it);
                path.start.y = ix;
            }

            path.grid.emplace_back(std::move(line));
        }

        path.bounds.width = path.grid.front().size();
        path.bounds.height = path.grid.size();

        return path;
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    auto path = PathChecker::from_input(std::ifstream{argv[1]});

    path.check(std::nullopt);
    fmt::println("part 1: {}", path.visited.size());

    std::unordered_set<aoc::pos, aoc::pos::hash> blocks;
    auto dir = 0;
    auto pos = path.start;
    while (true) {
        auto next = pos.move_by(PathChecker::dirs[dir]);
        if (!path.bounds.in_bounds(next)) {
            break;
        }

        if (path.is_blocked(next, std::nullopt)) {
            dir = PathChecker::next_dir(dir);
            continue;
        }

        // Check the whole path from the beginning, as the new block might obscure part of the original path, even
        // though it creates a cycle that starts at `pos`.
        if (path.check(next) == PathType::Cycle) {
            blocks.insert(next);
        }

        pos = next;
    }

    fmt::println("part 2: {}", blocks.size());

    return 0;
}
