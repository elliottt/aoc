load("//rules:solution.bzl", "aoc_solution", "aoc_solutions")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-9",
    solutions = [
        "solution-part-1",
        "solution-part-2",
    ],
)

cc_library(
    name = "graph",
    srcs = ["graph.cc"],
    hdrs = ["graph.h"],
    deps = ["@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "part-1",
    srcs = ["part-1.cc"],
    deps = ["graph", "@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)

aoc_solution(
    name = "solution-part-1",
    binary = "part-1",
    input = "input.txt",
)

cc_binary(
    name = "part-2",
    srcs = ["part-2.cc"],
    deps = ["graph", "@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)

aoc_solution(
    name = "solution-part-2",
    binary = "part-2",
    input = "input.txt",
)
