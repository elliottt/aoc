load("//rules:solution.bzl", "aoc_solutions", "aoc_tests")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-01",
    input = "input.txt",
    solutions = [ "solution" ],
)

aoc_tests(
    name = "tests",
    input = "test.txt",
    solution = "solution",
    spec = {
        "part 1": "24000",
        "part 2": "45000",
    }
)

cc_binary(
    name = "solution",
    srcs = ["solution.cc"],
    deps = ["@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
