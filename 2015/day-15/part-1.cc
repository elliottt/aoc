#include <fmt/core.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <regex>
#include <string>
#include <vector>

namespace views = ranges::views;

struct properties {
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;

    static constexpr properties empty() {
        return {0, 0, 0, 0, 0};
    }

    properties operator*(int n) const {
        return {capacity * n, durability * n, flavor * n, texture * n, calories * n};
    }

    properties operator+(const properties &other) const {
        return {
            capacity + other.capacity,
            durability + other.durability,
            flavor + other.flavor,
            texture + other.texture,
            calories + other.calories,
        };
    }

    int total() const {
        return std::max(0, capacity) * std::max(0, durability) * std::max(0, flavor) * std::max(0, texture);
    }
};

struct ingredient {
    std::string name;
    properties props;

    static ingredient parse(const std::string &line) {
        auto words = line | views::tokenize(std::regex{"[\\w-]+"}) | ranges::to<std::vector>();
        return {words[0], {stoi(words[2]), stoi(words[4]), stoi(words[6]), stoi(words[8]), stoi(words[10])}};
    }

    void print() {
        fmt::print(
            "{:>12}: {:>2}, {:>2}, {:>2}, {:>2}, {:>2}\n",
            name,
            props.capacity,
            props.durability,
            props.flavor,
            props.texture,
            props.calories);
    }

    properties use(int n) const {
        return props * n;
    }
};

bool validate(const std::vector<ingredient> &ingredients, const std::vector<int> &amounts) {

    auto summed = ranges::accumulate(
        views::zip_with([](auto &i, auto amount) { return i.props * amount; }, ingredients, amounts),
        properties::empty());

    return summed.total() > 0;
}

auto combinations() {
    auto values = views::ints(1, 98);
    return views::cartesian_product(values, values, values, values) | views::filter([](auto p) {
               return 100 == (std::get<0>(p) + std::get<1>(p) + std::get<2>(p) + std::get<3>(p));
           });
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    std::vector<ingredient> ingredients{};

    {
        std::ifstream in{argv[1]};
        ingredients = ranges::getlines(in) | views::transform([](auto &line) { return ingredient::parse(line); }) |
                      ranges::to<std::vector>();
    }

    auto max_val = 0;
    for (auto const &p : combinations()) {
        auto aggregate = (ingredients[0].props * std::get<0>(p)) + (ingredients[1].props * std::get<1>(p)) +
                         (ingredients[2].props * std::get<2>(p)) + (ingredients[3].props * std::get<3>(p));

        auto total = aggregate.total();
        max_val = std::max(max_val, total);
    }

    fmt::print("part 1: {}\n", max_val);

    return 0;
}
