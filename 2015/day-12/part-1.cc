#include <fmt/core.h>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

struct counter : nlohmann::json_sax<json> {
    virtual bool null() final {
        return true;
    }

    virtual bool boolean(bool val) final {
        return true;
    }

    virtual bool number_integer(number_integer_t val) final {
        total += val;
        return true;
    }

    virtual bool number_unsigned(number_unsigned_t val) final {
        total += val;
        return true;
    }

    virtual bool number_float(number_float_t val, const string_t &str) final {
        return true;
    }

    virtual bool string(string_t &val) final {
        return true;
    }

    virtual bool binary(binary_t &val) final {
        return true;
    }

    virtual bool start_object(std::size_t elements) final {
        return true;
    }

    virtual bool end_object() final {
        return true;
    }

    virtual bool start_array(std::size_t elements) final {
        return true;
    }

    virtual bool end_array() final {
        return true;
    }

    virtual bool key(string_t &val) final {
        return true;
    }

    virtual bool
    parse_error(std::size_t position, const string_t &last_token, const nlohmann::detail::exception &e) final {
        return false;
    }

    int total{0};
};

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    counter c;
    {
        ifstream in{argv[1]};
        json::sax_parse(in, &c);
    }

    fmt::print("part 1: {}\n", c.total);

    return 0;
}
