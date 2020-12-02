load("//rules:solution.bzl", "aoc_solutions")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-13",
    input = "input.txt",
    solutions = [
        "solution-part-1",
        "solution-part-2",
    ],
)

cc_library(
    name = "graph",
    srcs = ["graph.h", "graph.cc"],
    hdrs = ["graph.h"],
    deps = ["@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "part-1",
    srcs = ["part-1.cc"],
    deps = ["@range-v3", "@fmt", "graph"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "part-2",
    srcs = ["part-2.cc"],
    deps = ["@range-v3", "@fmt", "graph"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
