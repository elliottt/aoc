load("//rules:solution.bzl", "aoc_solutions", "aoc_tests")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-01",
    input = "input.txt",
    solutions = [ "solution" ],
)

aoc_tests(
    name = "tests1",
    input = "test1.txt",
    solution = "solution",
    spec = {
        "part 1": "142",
    }
)

aoc_tests(
    name = "tests2",
    input = "test2.txt",
    solution = "solution",
    spec = {
        "part 2": "281",
    }
)

cc_binary(
    name = "solution",
    srcs = ["solution.cc"],
    deps = ["@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
