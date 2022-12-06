#include <fmt/format.h>
#include <fstream>
#include <range/v3/all.hpp>
#include <string>
#include <vector>

namespace views = ranges::views;

class Distinct final {
    size_t window;
    std::string_view buffer;

public:
    Distinct(size_t window, std::string_view buffer) : window{window}, buffer{buffer} {}

    bool operator()(size_t offset) const {
        auto str = this->buffer.substr(offset, this->window);
        return ranges::all_of(views::iota(0U, this->window - 1), [str](auto i) {
            return str.substr(i + 1).find(str[i]) == str.npos;
        });
    }
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    std::string datastream;
    {
        std::ifstream in{argv[1]};
        in >> datastream;
    }

    {
        auto rng = views::iota(0U, datastream.size());
        auto res = ranges::find_if(rng, Distinct{4, datastream});
        assert(res != ranges::end(rng));
        fmt::print("part 1: {}\n", *res + 4);
    }

    {
        auto rng = views::iota(0U, datastream.size());
        auto res = ranges::find_if(rng, Distinct{14, datastream});
        assert(res != ranges::end(rng));
        fmt::print("part 2: {}\n", *res + 14);
    }

    return 0;
}
