
#include <iterator>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>
#include <fmt/core.h>
#include <range/v3/all.hpp>

using namespace std;

string md5(string input) {
    using boost::uuids::detail::md5;

    md5 hash;
    hash.process_bytes(input.data(), input.size());

    md5::digest_type digest;
    hash.get_digest(digest);

    string result;
    const auto intDigest = reinterpret_cast<const int *>(&digest);
    boost::algorithm::hex(intDigest, intDigest + (sizeof(md5::digest_type) / sizeof(int)), back_inserter(result));

    return result;
}

int leading_zeros(string digest) {
    using namespace ranges;
    return ranges::count(digest | views::take_while([](auto c) { return c == '0'; }), '0');
}

int main(int argc, char **argv) {
    using namespace ranges;

    auto res = views::iota(1)
        | views::transform([](auto i) -> pair<int, int> {
            auto digest = md5("iwrupvqb" + std::to_string(i));
            return {i, leading_zeros(digest)};
          })
        | views::drop_while([](auto p) { return p.second != 5; })
        | views::take(1)
        | ranges::to<vector<pair<int,int>>>();

    fmt::print("part-1: {}\n", res.front().first);

    return 0;
}
