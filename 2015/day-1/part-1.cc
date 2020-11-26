#include <algorithm>
#include <fmt/core.h>
#include <fstream>
#include <iterator>
#include <string>

using namespace std;

int eval_directions(std::string_view directions) {
    int floor = 0;
    for (auto c : directions) {
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
    }
    return floor;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    ifstream in{argv[1]};
    std::string out;

    std::copy(istream_iterator<char>{in}, istream_iterator<char>{},
              back_inserter(out));

    fmt::print("part 1: {}\n", eval_directions(out));

    return 0;
}
