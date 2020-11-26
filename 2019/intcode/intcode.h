#ifndef INTCODE_H
#define INTCODE_H

#include <filesystem>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>

namespace intcode {

class machine {
public:
    using address = int;

    enum class op {
        add = 1,
        mul = 2,
        halt = 99,
    };

    static machine load(std::filesystem::path path);
    static machine load(std::istream &in);

    int read(address addr) const;
    void write(address addr, int value);

    void run();

    machine();
    explicit machine(std::vector<int> memory);

private:
    std::vector<int> memory;

    std::tuple<address, address, address> decode3(int pc);
};

} // namespace intcode

#endif
