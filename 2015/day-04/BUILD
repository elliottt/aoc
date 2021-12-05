load("//rules:solution.bzl", "aoc_solutions")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-04",
    solutions = ["part-1","part-2"],
)

cc_binary(
    name = "part-1",
    srcs = ["part-1.cc"],
    deps = ["@range-v3", "@fmt", "@boost//:algorithm", "@boost//:conversion", "@boost//:uuid"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "part-2",
    srcs = ["part-2.cc"],
    deps = ["@range-v3", "@fmt", "@boost//:algorithm", "@boost//:conversion", "@boost//:uuid"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
