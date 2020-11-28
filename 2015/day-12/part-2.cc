#include <fmt/core.h>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

struct counter : nlohmann::json_sax<json> {
    virtual bool null() final { return true; }

    virtual bool boolean(bool val) final { return true; }

    virtual bool number_integer(number_integer_t val) final {
        stack.back().total += val;
        return true;
    }

    virtual bool number_unsigned(number_unsigned_t val) final {
        stack.back().total += val;
        return true;
    }

    virtual bool number_float(number_float_t val, const string_t &str) final {
        return true;
    }

    virtual bool string(string_t &val) final {
        if (val == "red") {
            stack.back().found_red = true;
        }
        return true;
    }

    virtual bool binary(binary_t &val) final { return true; }

    virtual bool start_object(std::size_t elements) final {
        stack.emplace_back();
        return true;
    }

    virtual bool end_object() final {
        bool found_red = stack.back().found_red;
        auto total = stack.back().total;
        stack.pop_back();

        if (!found_red) {
            stack.back().total += total;
        }
        return true;
    }

    virtual bool start_array(std::size_t elements) final {
        stack.emplace_back();
        return true;
    }

    virtual bool end_array() final {
        auto total = stack.back().total;
        stack.pop_back();
        stack.back().total += total;
        return true;
    }

    virtual bool key(string_t &val) final { return true; }

    virtual bool parse_error(std::size_t position, const string_t &last_token,
                             const nlohmann::detail::exception &e) final {
        return false;
    }

    struct object_state {
        bool found_red{false};
        int total{0};
    };

    vector<object_state> stack{{}};

    int get_total() const {
        return stack.back().total;
    }
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

    fmt::print("part 2: {}\n", c.get_total());

    return 0;
}
