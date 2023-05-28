load("//rules:solution.bzl", "aoc_solutions", "aoc_tests")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-03",
    input = "day-03.input.txt",
    solutions = [ "solution-03" ],
)


aoc_tests(
    name = "test-day-03",
    input = "day-03.test.txt",
    solution = "solution-03",
    spec = {
        "part 1": "31",
    },
)

cc_binary(
    name = "solution-03",
    srcs = ["day-03.cc"],
    deps = ["@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
