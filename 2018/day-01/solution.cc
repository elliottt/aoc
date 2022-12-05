#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <set>
#include <string>
#include <vector>

namespace views = ranges::views;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::vector<int> changes;

    {
        std::ifstream in{argv[1]};
        changes = ranges::getlines(in) | views::transform([](auto &line) {
                      if (line[0] == '+') {
                          return std::stoi(line.substr(1));
                      } else {
                          return std::stoi(line);
                      }
                  }) |
                  ranges::to<std::vector>;
    }

    fmt::print("part 1: {}\n", ranges::accumulate(changes, 0, ranges::plus{}));

    std::set<int> seen;
    int acc = 0;
    bool running = true;
    while (running) {
        for (auto x : changes) {
            acc += x;
            if (seen.contains(acc)) {
                running = false;
                break;
            }
            seen.insert(acc);
        }
    }

    fmt::print("part 2: {}\n", acc);

    return 0;
}
