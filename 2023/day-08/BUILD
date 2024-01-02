load("//rules:solution.bzl", "aoc_solutions", "aoc_tests")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-08",
    input = "input.txt",
    solutions = [ "solution" ],
)

test_suite(
    name = "test",
    tests = [ "test1", "test2", "test3" ],
)

aoc_tests(
    name = "test1",
    input = "test1.txt",
    solution = "solution",
    spec = {
        "part 1": "2",
    },
)

aoc_tests(
    name = "test2",
    input = "test2.txt",
    solution = "solution",
    spec = {
        "part 1": "6",
    },
)

aoc_tests(
    name = "test3",
    input = "test3.txt",
    solution = "solution",
    spec = {
        "part 2": "6",
    },
)

cc_binary(
    name = "solution",
    srcs = ["solution.cc"],
    deps = ["//common", "@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
