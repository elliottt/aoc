load("//rules:solution.bzl", "aoc_solutions")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-07",
    input = "input.txt",
    solutions = [ "solution" ],
)

cc_binary(
    name = "solution",
    srcs = ["solution.cc"],
    deps = ["@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
