#include <fmt/core.h>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>

#include <range/v3/all.hpp>

using namespace std;

int ribbon_required(string line) {
    auto a = line.find('x');
    auto b = line.find('x', a+1);

    auto l = stoi(line.substr(0, a));
    auto w = stoi(line.substr(a+1, b-a));
    auto h = stoi(line.substr(b+1, string::npos));

    auto wrap = 2 * std::min({l+w, w+h, h+l});
    auto bow = l*w*h;

    return wrap + bow;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    vector<string> input;
    {
        ifstream in{argv[1]};
        std::copy(istream_iterator<string>{in}, istream_iterator<string>{}, back_inserter(input));
    }

    fmt::print("part 2: {}\n", ranges::accumulate(input | ranges::views::transform(ribbon_required), 0));

    return 0;
}
