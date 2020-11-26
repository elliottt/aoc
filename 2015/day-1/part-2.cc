#include <algorithm>
#include <fmt/core.h>
#include <fstream>
#include <iterator>
#include <string>

using namespace std;

int first_basement_position(std::string_view directions) {
    int floor = 0;
    int position = 0;
    for (auto c : directions) {
        ++position;

        switch (c) {
        case '(':
            ++floor;
            break;
        case ')':
            --floor;
            break;
        default:
            break;
        }

        if (floor < 0) {
            break;
        }
    }
    return position;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    ifstream in{argv[1]};
    std::string out;

    std::copy(istream_iterator<char>{in}, istream_iterator<char>{},
              back_inserter(out));

    fmt::print("part 2: {}\n", first_basement_position(out));

    return 0;
}
