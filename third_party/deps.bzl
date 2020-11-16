load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def deps():
    http_archive(
        name = "range-v3",
        urls = ["https://github.com/ericniebler/range-v3/archive/0.11.0.tar.gz"],
        sha256 = "376376615dbba43d3bef75aa590931431ecb49eb36d07bb726a19f680c75e20c",
        strip_prefix = "range-v3-0.11.0",
    )

    http_archive(
        name = "fmt",
        urls = ["https://github.com/fmtlib/fmt/archive/7.0.3.tar.gz"],
        sha256 = "b4b51bc16288e2281cddc59c28f0b4f84fed58d016fb038273a09f05f8473297",
        build_file = "//third_party:fmt.BUILD",
        strip_prefix = "fmt-7.0.3",
    )
