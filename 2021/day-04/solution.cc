#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <regex>
#include <string>
#include <vector>

namespace views = ranges::views;

struct cell {
    bool marked;
    int val;

    cell(int val) : marked{false}, val{val} {}
};

using board = std::vector<cell>;

auto columns(const board &board) {
    return views::iota(0, 5) | views::transform([&board](auto offset) {
               return board | views::drop(offset) | views::chunk(5) |
                      views::transform([](auto &&chunk) { return *chunk.begin(); });
           });
}

auto rows(const board &board) {
    return board | views::chunk(5);
}

bool board_wins(const board &board) {
    for (auto &&col : columns(board)) {
        if (ranges::all_of(col, [](auto const &cell) { return cell.marked; })) {
            return true;
        }
    }

    for (auto &&row : rows(board)) {
        if (ranges::all_of(row, [](auto const &cell) { return cell.marked; })) {
            return true;
        }
    }

    return false;
}

auto unmarked(const board &board) {
    return board | views::filter([](auto &cell) { return !cell.marked; }) |
           views::transform([](auto &cell) { return cell.val; });
}

void part_1(const std::vector<int> &numbers, std::vector<board> boards) {
    for (auto num : numbers) {
        for (auto &board : boards) {
            auto entry = ranges::find(board, num, &cell::val);
            if (entry != ranges::end(board)) {
                entry->marked = true;
            }

            if (board_wins(board)) {
                auto score = ranges::accumulate(unmarked(board), 0);
                fmt::print("part 1: {}\n", score * num);
                return;
            }
        }
    }

    throw std::logic_error("no board won");
}

void part_2(const std::vector<int> &numbers, std::vector<board> boards) {
    std::vector<int> wins;

    for (auto num : numbers) {
        boards.erase(
            ranges::remove_if(
                boards,
                [num, &wins](auto &board) {
                    auto entry = ranges::find(board, num, &cell::val);
                    if (entry != ranges::end(board)) {
                        entry->marked = true;
                    }

                    if (board_wins(board)) {
                        auto score = ranges::accumulate(unmarked(board), 0);
                        wins.push_back(score * num);
                        return true;
                    }

                    return false;
                }),
            ranges::end(boards));
    }

    fmt::print("part 2: {}\n", wins.back());
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    std::vector<int> numbers;
    std::vector<board> boards;

    {
        std::ifstream in{argv[1]};

        std::string line;
        std::getline(in, line);

        numbers = line | views::split(',') | views::transform([](auto &&rng) {
                      std::string str(&*rng.begin(), ranges::distance(rng));
                      return std::stoi(str);
                  }) |
                  ranges::to<std::vector<int>>;

        for (auto &&rng : ranges::getlines(in) | views::chunk(6)) {
            auto &board = boards.emplace_back();
            for (auto &&line : views::drop(rng, 1)) {
                for (auto &&num : views::tokenize(line, std::regex{"[0-9]+"})) {
                    board.emplace_back(std::stoi(num));
                }
            }
        }
    }

    part_1(numbers, boards);
    part_2(numbers, boards);

    return 0;
}
