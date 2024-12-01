load("//rules:solution.bzl", "aoc_solutions", "aoc_tests")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-01",
    input = "input.txt",
    solutions = [ "solution" ],
)

aoc_tests(
    name = "test",
    input = "test.txt",
    solution = "solution",
    spec = {
        "part 1": "11",
        "part 2": "31",
    },
)

aoc_tests(
    name = "problem",
    input = "input.txt",
    solution = "solution",
    spec = {
        "part 1": "1941353",
        "part 2": "22539317",
    },
)

cc_binary(
    name = "solution",
    srcs = ["solution.cc"],
    deps = ["//common", "@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
