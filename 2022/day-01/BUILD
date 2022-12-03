load("//rules:solution.bzl", "aoc_solutions", "aoc_test")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-01",
    input = "input.txt",
    solutions = [ "solution" ],
)

aoc_test(
    name = "test1",
    input = "test.txt",
    solution = "solution",
    result = "part 1",
    expected = "24000",
)

aoc_test(
    name = "test2",
    input = "test.txt",
    solution = "solution",
    result = "part 2",
    expected = "45000",
)

cc_binary(
    name = "solution",
    srcs = ["solution.cc"],
    deps = ["@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
