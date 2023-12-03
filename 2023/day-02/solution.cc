#include <charconv>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

struct Round {
    int red = 0;
    int green = 0;
    int blue = 0;

    static Round parse(std::string_view round) {
        Round result{};

        for (auto &&chunk : views::split(round, ',')) {
            auto front = ranges::find_if(chunk, [](auto c) { return !std::isspace(c); });
            std::string_view str(&*front, ranges::distance(front, ranges::end(chunk)));

            int n;
            std::from_chars(str.begin(), str.end(), n);

            str = str.substr(str.find(' ') + 1);
            if (str == "red") {
                result.red += n;
            } else if (str == "green") {
                result.green += n;
            } else if (str == "blue") {
                result.blue += n;
            } else {
                fmt::print("unknown color {}\n", str);
                std::abort();
            }
        }

        return result;
    }

    bool possible(int red, int green, int blue) const {
        return this->red <= red && this->green <= green && this->blue <= blue;
    }
};

struct Game {
    int n = 0;
    std::vector<Round> rounds;

    static Game parse(std::string_view line) {
        Game result{};

        // skip "Game "
        line = line.substr(5);

        // parse the number
        auto colon = line.find(':');
        auto [ptr, ec] = std::from_chars(line.begin(), line.begin() + colon, result.n);

        line = line.substr(colon + 2);

        for (auto &&chunk : views::split(line, ';')) {
            std::string_view round(&*chunk.begin(), ranges::distance(chunk));
            round = round.substr(round.find_first_not_of(" "));
            result.rounds.emplace_back(Round::parse(round));
        }

        return result;
    }

    bool possible(int red, int green, int blue) const {
        return ranges::all_of(this->rounds, [red, green, blue](auto &round) {
            return round.possible(red, green, blue);
        });
    }

    int power() const {
        auto red = ranges::max(views::transform(this->rounds, [](auto &round) { return round.red; }));
        auto green = ranges::max(views::transform(this->rounds, [](auto &round) { return round.green; }));
        auto blue = ranges::max(views::transform(this->rounds, [](auto &round) { return round.blue; }));

        return red * green * blue;
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::vector<Game> games;

    {
        std::ifstream in{argv[1]};

        games = ranges::getlines(in) | views::transform(Game::parse) | ranges::to<std::vector>;
    }

    {
        auto answer = ranges::accumulate(
            views::filter(games, [](auto &game) { return game.possible(12, 13, 14); }) |
                views::transform([](auto &game) { return game.n; }),
            0);

        fmt::print("part 1: {}\n", answer);
    }

    {
        auto answer = ranges::accumulate(views::transform(games, [](auto &game) { return game.power(); }), 0);

        fmt::print("part 2: {}\n", answer);
    }

    return 0;
}
