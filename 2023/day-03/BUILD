load("//rules:solution.bzl", "aoc_solutions", "aoc_tests")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-03",
    input = "input.txt",
    solutions = [ "solution" ],
)

aoc_tests(
    name = "test",
    input = "test.txt",
    solution = "solution",
    spec = {
        "part 1": "4361",
        "part 2": "467835",
    },
)

cc_binary(
    name = "solution",
    srcs = ["solution.cc"],
    deps = ["//common", "@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
