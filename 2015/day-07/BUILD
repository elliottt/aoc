load("//rules:solution.bzl", "aoc_solutions")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-07",
    input = "input.txt",
    solutions = [ "part-1", "part-2" ],
)

cc_library(
    name = "wires",
    srcs = ["wires.cc", "wires.h"],
    hdrs = ["wires.h"],
    deps = ["@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "part-1",
    srcs = ["part-1.cc"],
    deps = ["wires", "@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "part-2",
    srcs = ["part-2.cc"],
    deps = ["wires", "@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
