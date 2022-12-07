#include <cassert>
#include <charconv>
#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <unordered_map>
#include <vector>

namespace views = ranges::views;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::vector<size_t> sizes;
    {
        std::unordered_map<std::string, std::unique_ptr<size_t>> dirs;
        std::vector<std::pair<std::string, size_t *>> work;
        std::string cwd;
        std::ifstream in{argv[1]};
        for (auto buf : ranges::getlines(in)) {
            std::string_view line{buf};

            if (line == "$ ls" || line.starts_with("dir ")) {
                continue;
            }

            if (line.starts_with("$ cd ")) {
                auto subdir = line.substr(5);
                if (subdir == "..") {
                    work.pop_back();
                    cwd = work.back().first;
                } else {
                    cwd.append(subdir);
                    auto [dir, _] = dirs.emplace(cwd, std::make_unique<size_t>(0));
                    work.emplace_back(cwd, dir->second.get());
                }
                continue;
            }

            size_t value;
            std::from_chars(line.begin(), line.end(), value);

            for (auto &dir : work) {
                *dir.second += value;
            }
        }

        sizes = views::transform(dirs, [](auto &entry) { return *(entry.second); }) | ranges::to<std::vector> |
                ranges::actions::sort;
    }

    fmt::print(
        "part 1: {}\n",
        ranges::accumulate(views::transform(sizes, [](auto val) { return val <= 100000U ? val : 0; }), 0U));

    auto total = sizes.back();
    auto available = 70000000 - total;
    assert(available < 30000000);
    auto needed = 30000000 - available;

    std::vector<size_t> sorted = views::filter(sizes, [needed](auto val) { return val >= needed; }) |
                                 ranges::to<std::vector> | ranges::actions::sort;
    fmt::print("part 2: {}\n", sorted.front());

    return 0;
}
