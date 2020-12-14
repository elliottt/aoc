#include <fmt/core.h>
#include <fstream>
#include <map>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace ranges;

void generate_masks_aux(vector<pair<uint64_t, uint64_t>> &masks,
                        uint64_t floating, uint64_t ones, uint64_t zeros,
                        int bit) {
    if (bit >= 36) {
        masks.emplace_back(ones, zeros);
        return;
    }

    auto mask = 1L << bit;
    if (floating & mask) {
        generate_masks_aux(masks, floating, ones, zeros & ~mask, bit + 1);
        generate_masks_aux(masks, floating, ones | mask, zeros, bit + 1);
    } else {
        generate_masks_aux(masks, floating, ones, zeros, bit + 1);
    }
}

void generate_masks(vector<pair<uint64_t, uint64_t>> &masks, uint64_t floating,
                    uint64_t ones) {
    generate_masks_aux(masks, floating, ones, (1L << 36) - 1L, 0);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    map<uint64_t, uint64_t> memory{};
    {
        ifstream in{argv[1]};

        vector<pair<uint64_t, uint64_t>> masks{};

        for (auto const &line : getlines(in)) {
            if (line.find("mask = ") == 0) {
                masks.clear();

                uint64_t ones{0};
                uint64_t floating{0};

                for (auto const &[ix, c] :
                     line | views::drop(7) | views::enumerate) {
                    auto bit = 35 - ix;
                    switch (c) {
                    case '1':
                        ones |= 1L << bit;
                        break;
                    case '0':
                        break;
                    case 'X':
                        floating |= 1L << bit;
                        break;
                    }
                }

                generate_masks(masks, floating, ones);
                ranges::sort(masks);
            } else {
                uint64_t base{0L};
                {
                    auto end = line.find("]", 4);
                    base = stol(line.substr(4, end - 4));
                }

                uint64_t val{0};
                {
                    uint64_t pos = line.find(" = ");
                    val = stol(line.substr(pos + 3));
                }

                for (auto const &[ones, zeros] : masks) {
                    uint64_t addr = (base | ones) & zeros;
                    memory[addr] = val;
                }
            }
        }
    }

    uint64_t sum{0};
    for (auto const &entry : memory) {
        sum += entry.second;
    }

    fmt::print("part 2: {}\n", sum);

    return 0;
}
