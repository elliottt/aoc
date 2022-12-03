load("//rules:solution.bzl", "aoc_solutions", "aoc_test")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-03",
    input = "input.txt",
    solutions = [ "solution" ],
)

aoc_test(
    name = "test1",
    input = "test.txt",
    solution = "solution",
    result = "part 1",
    expected = "157",
)

aoc_test(
    name = "test2",
    input = "test.txt",
    solution = "solution",
    result = "part 2",
    expected = "70",
)

cc_binary(
    name = "solution",
    srcs = ["solution.cc"],
    deps = ["//common", "@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
