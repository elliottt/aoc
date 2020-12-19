load("//rules:solution.bzl", "aoc_solutions")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-17",
    input = "input.txt",
    solutions = [ "part-1", "part-2" ],
)

cc_library(
    name = "dense-intmap",
    srcs = ["dense-intmap.h"],
    hdrs = ["dense-intmap.h"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "part-1",
    srcs = ["part-1.cc"],
    deps = ["@range-v3", "@fmt", "dense-intmap"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "part-2",
    srcs = ["part-2.cc"],
    deps = ["@range-v3", "@fmt", "dense-intmap"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
