load("//rules:solution.bzl", "aoc_solutions", "aoc_tests")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-02",
    input = "input.txt",
    solutions = [ "solution" ],
)

aoc_tests(
    name = "test1",
    input = "test.txt",
    solution = "solution",
    spec = {
        "part 1": "12",
    },
)

aoc_tests(
    name = "test2",
    input = "test2.txt",
    solution = "solution",
    spec = {
        "part 2": "fgij",
    },
)

cc_binary(
    name = "solution",
    srcs = ["solution.cc"],
    deps = ["//common", "@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
