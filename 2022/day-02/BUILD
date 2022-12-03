load("//rules:solution.bzl", "aoc_solutions", "aoc_test")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-02",
    input = "input.txt",
    solutions = [ "solution" ],
)

aoc_test(
    name = "test1",
    solution = "solution",
    input = "test.txt",
    result = "part 1",
    expected = "15",
)

aoc_test(
    name = "test2",
    solution = "solution",
    input = "test.txt",
    result = "part 2",
    expected = "12",
)

cc_binary(
    name = "solution",
    srcs = ["solution.cc"],
    deps = ["@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
