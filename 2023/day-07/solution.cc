#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

enum class Type {
    None = 0,
    HighCard = 1,
    OnePair = 2,
    TwoPair = 3,
    ThreeOfAKind = 4,
    FullHouse = 5,
    FourOfAKind = 6,
    FiveOfAKind = 7,
};

auto get_counts(std::span<int> cards) {
    auto sorted = cards | ranges::to<std::vector> | ranges::actions::sort;

    return views::chunk_by(sorted, ranges::equal_to{}) | views::transform([](auto &&rng) {
               auto size = ranges::size(rng);
               auto val = *ranges::begin(rng);
               return std::make_pair(val, size);
           }) |
           ranges::to<std::vector> | ranges::actions::sort(ranges::less{}, [](auto p) { return p.second; });
}

struct Hand {
    std::vector<int> cards;
    int bid{0};
    Type type{Type::None};

    static constexpr const int JOKER = 1;
    static constexpr const int JACK = 11;

    Hand() = default;

    Hand(std::vector<int> cards, int bid) : cards{std::move(cards)}, bid{bid} {
        assert(this->cards.size() == 5);

        auto counts = get_counts(this->cards);

        int jokers = 0;

        counts.erase(
            ranges::remove_if(
                counts,
                [&jokers](auto &p) {
                    if (p.first == JOKER) {
                        jokers += p.second;
                        return true;
                    }
                    return false;
                }),
            counts.end());

        if (!counts.empty()) {
            counts.back().second += jokers;
        }

        switch (counts.size()) {
        case 0:
            // everything was a joker, fall-through to the five-of-a-kind case
        case 1:
            this->type = Type::FiveOfAKind;
            break;
        case 2:
            if (counts[0].second == 1) {
                this->type = Type::FourOfAKind;
            } else {
                this->type = Type::FullHouse;
            }

            break;
        case 3:
            if (counts[0].second == 1 && counts[1].second == 1) {
                this->type = Type::ThreeOfAKind;
            } else {
                this->type = Type::TwoPair;
            }
            break;
        case 4:
            this->type = Type::OnePair;
            break;
        default:
            assert(counts.size() == 5);
            this->type = Type::HighCard;
            break;
        }

        assert(this->type != Type::None);
    }

    void set_type(bool joker) {}

    static Hand parse_no_jokers(std::string_view str) {
        return Hand::parse(str, JACK);
    }

    static Hand parse_jokers(std::string_view str) {
        return Hand::parse(str, JOKER);
    }

    static Hand parse(std::string_view str, int joker) {
        auto cards = str.substr(0, 5) | views::transform([joker](auto c) {
                         int r = c - '0';
                         if (r < 10) {
                             return r;
                         }
                         switch (c) {
                         case 'T':
                             return 10;
                         case 'J':
                             return joker;
                         case 'Q':
                             return 12;
                         case 'K':
                             return 13;
                         case 'A':
                             return 14;
                         default:
                             return 0;
                         }
                     }) |
                     ranges::to<std::vector>;

        auto bid = std::stoi(std::string{str.substr(6)});

        return Hand{std::move(cards), bid};
    }

    bool operator<(const Hand &other) const {
        if (this->type != other.type) {
            return this->type < other.type;
        }

        assert(this->cards.size() == other.cards.size());
        for (auto [a, b] : views::zip(this->cards, other.cards)) {
            if (a < b) {
                return true;
            }

            if (a > b) {
                return false;
            }
        }

        return false;
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::vector<std::string> lines;
    std::vector<Hand> no_jokers;
    std::vector<Hand> jokers;

    {
        std::ifstream in{argv[1]};
        lines = ranges::getlines(in) | ranges::to<std::vector>;
        no_jokers = lines | views::transform(Hand::parse_no_jokers) | ranges::to<std::vector>;
        jokers = lines | views::transform(Hand::parse_jokers) | ranges::to<std::vector>;
    }

    auto compute_total = [](const std::vector<Hand> &hands) {
        return ranges::accumulate(
            hands | views::enumerate | views::transform([](auto p) {
                auto [ix, hand] = p;
                auto rank = ix + 1;
                return rank * hand.bid;
            }),
            0ul);
    };

    std::sort(no_jokers.begin(), no_jokers.end(), [](auto &l, auto &r) { return l < r; });
    fmt::print("part 1: {}\n", compute_total(no_jokers));

    std::sort(jokers.begin(), jokers.end(), [](auto &l, auto &r) { return l < r; });
    fmt::print("part 2: {}\n", compute_total(jokers));

    return 0;
}
