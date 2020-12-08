load("//rules:solution.bzl", "aoc_solutions")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-20",
    solutions = [ "part-1" ],
)

cc_binary(
    name = "part-1",
    srcs = ["part-1.cc"],
    deps = ["@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
