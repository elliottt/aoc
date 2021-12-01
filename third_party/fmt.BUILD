
cc_library(
    name = "fmt",
    srcs = glob(["include/fmt/*.h"]) + ["src/format.cc", "src/os.cc"],
    hdrs = [
        "include/fmt/core.h",
        "include/fmt/format.h"
    ],
    includes = ["include"],
    strip_include_prefix = "include",
    copts = ["-std=c++20"],
    visibility = ["//visibility:public"],
)
