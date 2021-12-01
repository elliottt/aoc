#include <fmt/core.h>
#include <fstream>
#include <map>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

using std::ifstream, std::string, std::vector, std::map;
using namespace ranges;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    map<uint64_t, uint64_t> memory{};
    const uint64_t value_mask{(1L << 36) - 1L};

    {
        ifstream in{argv[1]};

        uint64_t ones_mask{0};
        uint64_t zeros_mask = -1;

        for (auto const &line : getlines(in)) {
            if (line.find("mask = ") == 0) {
                ones_mask = 0L;
                zeros_mask = value_mask;

                for (auto const &[ix, c] :
                     line | views::drop(7) | views::enumerate) {
                    auto bit = 35 - ix;
                    switch (c) {
                    case '1':
                        ones_mask |= 1L << bit;
                        break;
                    case '0':
                        zeros_mask ^= 1L << bit;
                        break;
                    }
                }
            } else {
                uint64_t addr{0L};
                {
                    auto end = line.find("]", 4);
                    addr = stol(line.substr(4, end - 4));
                    addr &= value_mask;
                }

                uint64_t pos = line.find(" = ");
                uint64_t val = stol(line.substr(pos + 3));
                val |= ones_mask;
                val &= zeros_mask;
                memory[addr] = val;
            }
        }
    }

    uint64_t sum{0};
    for (auto const &entry : memory) {
        sum += entry.second;
    }

    fmt::print("part 1: {}\n", sum);

    return 0;
}
