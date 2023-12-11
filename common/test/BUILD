load("//rules:config.bzl", "COPTS")

test_suite(
    name = "test",
    tests = ["test_math"],
)

cc_test(
    name = "test_math",
    srcs = ["test_math.cc"],
    deps = ["//common", "@fmt", "@doctest//doctest", "@doctest//doctest:main"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
