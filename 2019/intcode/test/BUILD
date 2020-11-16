test_suite(
    name = "test",
    tests = [
        "basic-op-tests",
    ],
)

cc_test(
    name = "basic-op-tests",
    srcs = ["basic-op-tests.cc"],
    deps = ["//2019/intcode", "@doctest", "@doctest//:doctest_main"],
    copts = ["-std=c++17"],
)
