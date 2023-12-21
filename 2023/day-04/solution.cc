#include <charconv>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <regex>
#include <string>
#include <vector>

namespace views = ranges::views;

struct Card {
    std::vector<int> winning;
    std::vector<int> hand;
    int matching;

    static Card parse(std::string_view line) {
        Card res{};

        auto colon = line.find(':');
        auto pipe = line.find('|');

        auto winning = line.substr(colon + 2, pipe - colon - 3);
        auto hand = line.substr(pipe + 2);

        std::string buf;
        for (const auto &word : views::tokenize(winning, std::regex{"[0-9]+"})) {
            buf = word;
            auto &i = res.winning.emplace_back();
            std::from_chars(buf.data(), buf.data() + buf.size(), i);
        }

        for (const auto &word : views::tokenize(hand, std::regex{"[0-9]+"})) {
            buf = word;
            auto &i = res.hand.emplace_back();
            std::from_chars(buf.data(), buf.data() + buf.size(), i);
        }

        res.matching = ranges::count_if(res.hand, [&res](auto n) { return ranges::contains(res.winning, n); });

        return res;
    }

    int score() const {
        if (this->matching == 0) {
            return 0;
        }

        return 1 << (this->matching - 1);
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::vector<Card> cards;

    {
        std::ifstream in{argv[1]};
        cards = ranges::getlines(in) | views::transform(Card::parse) | ranges::to<std::vector>;
    }

    fmt::print("part 1: {}\n", ranges::accumulate(cards, 0, ranges::plus{}, &Card::score));

    std::vector<int> multipliers(cards.size(), 1);

    for (auto [ix, card] : views::enumerate(cards)) {
        for (auto next : views::ints(ix + 1, ix + 1 + card.matching)) {
            multipliers[next] += multipliers[ix];
        }
    }

    fmt::print("part 2: {}\n", ranges::accumulate(multipliers, 0));

    return 0;
}
