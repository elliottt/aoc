
#include <boost/algorithm/hex.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <fmt/core.h>
#include <iterator>
#include <range/v3/all.hpp>

using namespace std;

struct count_zeros {

    bool only_zeros;
    int zeros;

    count_zeros() : only_zeros{true}, zeros{0} {}

    count_zeros &operator*() {
        return *this;
    }

    count_zeros &operator++() {
        return *this;
    }

    const count_zeros &operator++(int) {
        return *this;
    }

    count_zeros &operator=(const char c) {
        if (only_zeros && c == '0') {
            ++zeros;
        } else {
            only_zeros = false;
        }
        return *this;
    }
};

template <> struct std::iterator_traits<count_zeros> {
    using iterator_category = std::output_iterator_tag;
    using value_type = void;
};

int md5_leading_zeros(boost::uuids::detail::md5 hash, const string &input) {
    using boost::uuids::detail::md5;

    hash.process_bytes(input.data(), input.size());

    md5::digest_type digest;
    hash.get_digest(digest);

    const auto intDigest = reinterpret_cast<const int *>(&digest);

    auto zeros = boost::algorithm::hex(intDigest, intDigest + (sizeof(md5::digest_type) / sizeof(int)), count_zeros{});

    return zeros.zeros;
}

int main(int argc, char **argv) {
    using namespace ranges;

    boost::uuids::detail::md5 hash;
    hash.process_bytes("iwrupvqb", 8);

    string input;
    input.reserve(20);

    for (auto i : views::iota(1)) {
        input = to_string(i);
        if (md5_leading_zeros(hash, input) == 6) {
            fmt::print("part-2: {}\n", i);
            break;
        }
    }

    return 0;
}
