#include <cstdint>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <regex>
#include <string>
#include <vector>

namespace views = ranges::views;

struct Race {
    int64_t time;
    int64_t distance;

    size_t winning_times() const {
        auto check = [this](auto time) { return time * (this->time - time) > this->distance; };

        size_t start;
        for (start = 1; start < this->distance && !check(start); start++) {}

        size_t end;
        for (end = start+1; end < this->distance && check(end); end++) {}

        return end - start;
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::vector<Race> races;
    std::vector<std::string> lines;

    {
        std::ifstream in{argv[1]};
        lines = ranges::getlines(in) | ranges::to<std::vector>;
    }

    races = views::tokenize(lines[0], std::regex{"[0-9]+"}) | views::transform([](auto &&match) {
                return Race{std::stoi(match), 0};
            }) |
            ranges::to<std::vector>;

    for (auto [ix, match] : views::tokenize(lines[1], std::regex{"[0-9]+"}) | views::enumerate) {
        races[ix].distance = std::stoi(match);
    }

    fmt::print("part 1: {}\n", ranges::accumulate(races, 1l, ranges::multiplies{}, &Race::winning_times));

    Race race;

    race.time = std::stoll(views::filter(lines[0], [](auto c) { return std::isdigit(c); }) | ranges::to<std::string>);
    race.distance =
        std::stoll(views::filter(lines[1], [](auto c) { return std::isdigit(c); }) | ranges::to<std::string>);

    fmt::print("part 2: {}\n", race.winning_times());

    return 0;
}
