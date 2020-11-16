
cc_library(
    name = "fmt",
    srcs = glob(["src/*.cc", "include/fmt/*.h"]),
    hdrs = [
        "include/fmt/core.h",
        "include/fmt/format.h"
    ],
    includes = ["include"],
    strip_include_prefix = "include",
    copts = ["-std=c++17"],
    visibility = ["//visibility:public"],
)
