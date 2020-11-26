load("//rules:config.bzl", "COPTS")

cc_library(
    name = "intcode",
    srcs = glob(["*.cc", "*.h"]),
    hdrs = ["intcode.h"],
    deps = ["@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
