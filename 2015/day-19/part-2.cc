#include <cctype>
#include <climits>
#include <fmt/core.h>
#include <fmt/format.h>
#include <fstream>
#include <map>
#include <range/v3/all.hpp>
#include <regex>
#include <set>
#include <vector>

namespace views = ranges::views;

struct node {
    int steps{0};
    std::string current;
    std::shared_ptr<node> parent{nullptr};

    node(int steps, std::string &&current, const std::shared_ptr<node> &parent)
        : steps{steps}, current{std::move(current)}, parent{parent} {}
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    std::vector<std::pair<std::string, std::string>> rev_steps{};
    std::string input;

    std::regex match_chunk{"[[:upper:]][[:lower:]]*"};

    {
        std::ifstream in{argv[1]};
        auto lines = ranges::getlines(in) | ranges::to<std::vector>();

        for (auto &line : lines | views::delimit("")) {
            auto pos = line.find(" => ");
            auto key = line.substr(0, pos);
            auto rhs = line.substr(pos + 4);
            rev_steps.emplace_back(rhs, key);
        }

        ranges::actions::sort(rev_steps, ranges::greater{}, [](auto &p) { return p.first.size(); });

        input = lines.back();
    }

    std::deque<std::shared_ptr<node>> work{};
    {
        auto root = make_shared<node>(0, std::move(input), nullptr);
        work.emplace_back(std::move(root));
    }

    while (!work.empty()) {
        auto head = std::move(work.front());
        work.pop_front();

        if (head->current == "e") {
            fmt::print("part 2: {}\n", head->steps);
            return 0;
        }

        for (auto &rule : rev_steps) {
            auto pos = head->current.find(rule.first);
            if (pos != std::string::npos) {
                auto current = head->current;
                current.replace(pos, rule.first.size(), rule.second);
                auto child = make_shared<node>(head->steps + 1, std::move(current), head);
                work.emplace_back(std::move(child));
                ranges::push_heap(work, ranges::less{}, [](auto &n) { return n->steps; });
            }
        }
    }

    return 0;
}
