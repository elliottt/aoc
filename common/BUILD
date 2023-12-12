load("//rules:config.bzl", "COPTS")

cc_library(
    name = "common",
    srcs = glob(["*.cc", "*.h"]),
    hdrs = ["ca.h", "grid.h", "math.h", "pos.h", "interval.h"],
    deps = ["@fmt", "@range-v3"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
