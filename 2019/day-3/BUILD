load("//rules:config.bzl", "COPTS")

cc_library(
    name = "lines",
    srcs = ["lines.h", "lines.cc"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "part-1",
    srcs = ["part-1.cc"],
    deps = ["lines"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
