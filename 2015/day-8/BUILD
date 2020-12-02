load("//rules:solution.bzl", "aoc_solutions")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-8",
    input = "input.txt",
    solutions = [ "part-1", "part-2" ],
)

cc_binary(
    name = "part-1",
    srcs = ["part-1.cc"],
    deps = ["@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "part-2",
    srcs = ["part-2.cc"],
    deps = ["@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
