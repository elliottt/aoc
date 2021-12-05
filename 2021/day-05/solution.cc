#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>

namespace views = ranges::views;

struct pos {
    int x;
    int y;

    static pos parse(const std::string &str) {
        auto comma = str.find(",");

        pos res;
        res.x = std::stoi(str.substr(0, comma));
        res.y = std::stoi(str.substr(comma + 1));
        return res;
    }

    pos &operator+=(const pos &other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    bool operator==(const pos &other) const {
        return this->x == other.x && this->y == other.y;
    }

    bool operator!=(const pos &other) const {
        return !(*this == other);
    }
};

struct line {
    pos start;
    pos end;

    static line parse(const std::string &str) {
        auto arrow = str.find(" -> ");

        line res;
        res.start = pos::parse(str.substr(0, arrow));
        res.end = pos::parse(str.substr(arrow + 4));
        return res;
    }

    bool is_vertical() const {
        return this->start.x == this->end.x;
    }

    bool is_horizontal() const {
        return this->start.y == this->end.y;
    }

    void apply(std::vector<std::vector<int>> &board, bool allow_diagonal = false) {
        if (this->is_vertical()) {
            auto ys = views::iota(std::min(this->start.y, this->end.y), std::max(this->start.y, this->end.y) + 1);
            for (auto y : ys) {
                board[y][this->start.x] += 1;
            }
        } else if (this->is_horizontal()) {
            auto xs = views::iota(std::min(this->start.x, this->end.x), std::max(this->start.x, this->end.x) + 1);
            for (auto x : xs) {
                board[this->start.y][x] += 1;
            }
        } else if (allow_diagonal) {
            pos s;
            s.x = this->start.x < this->end.x ? 1 : -1;
            s.y = this->start.y < this->end.y ? 1 : -1;

            pos p = this->start;
            while (true) {
                board[p.y][p.x] += 1;

                if (p == this->end) {
                    break;
                }

                p += s;

            }
        }
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    std::vector<line> lines;
    {
        std::ifstream in{argv[1]};
        ranges::copy(ranges::getlines(in) | views::transform(line::parse), ranges::back_inserter(lines));
    }

    {
        std::vector<std::vector<int>> board(1000, std::vector<int>(1000, 0));

        for (auto &line : lines) {
            line.apply(board);
        }

        auto overlaps = ranges::accumulate(
            board |
                views::transform([](auto &col) { return ranges::count_if(col, [](auto cell) { return cell > 1; }); }),
            0);

        fmt::print("part 1: {}\n", overlaps);
    }

    {
        std::vector<std::vector<int>> board(1000, std::vector<int>(1000, 0));

        for (auto &line : lines) {
            line.apply(board, true);
        }

        auto overlaps = ranges::accumulate(
            board |
                views::transform([](auto &col) { return ranges::count_if(col, [](auto cell) { return cell > 1; }); }),
            0);

        fmt::print("part 2: {}\n", overlaps);
    }

    return 0;
}
