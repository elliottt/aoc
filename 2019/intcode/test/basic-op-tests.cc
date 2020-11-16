#include "doctest.h"

#include "2019/intcode/intcode.h"

using namespace intcode;

TEST_CASE("Add") {
    {
        machine program({1,0,0,0,99});
        program.run();
        CHECK_EQ(2, program.read(0));
    }

    {
        machine program({1,1,1,4,99,5,6,0,99});
        program.run();
        CHECK_EQ(30, program.read(0));
    }
}

TEST_CASE("Mul") {
    {
        machine program({2,3,0,3,99});
        program.run();
        CHECK_EQ(6, program.read(3));
    }

    {
        machine program({2,4,4,5,99,0});
        program.run();
        CHECK_EQ(9801, program.read(5));
    }
}
