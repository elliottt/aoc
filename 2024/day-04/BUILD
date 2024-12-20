load("//rules:solution.bzl", "aoc_solutions", "aoc_tests")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-04",
    input = "input.txt",
    solutions = [ "solution" ],
)

aoc_tests(
    name = "test1",
    input = "test1.txt",
    solution = "solution",
    spec = {
        "part 1": "18",
    },
)

aoc_tests(
    name = "test2",
    input = "test2.txt",
    solution = "solution",
    spec = {
        "part 2": "9",
    },
)

cc_binary(
    name = "solution",
    srcs = ["solution.cc"],
    deps = ["//common", "@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
