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

    http_archive(
        name = "doctest",
        urls = ["https://github.com/onqtam/doctest/archive/7d42bd0fab6c44010c8aed9338bd02bea5feba41.zip"],
        sha256 = "b33c8e954d15a146bb744ca29f4ca204b955530f52b2f8a895746a99cee4f2df",
        build_file = "//third_party:doctest.BUILD",
        strip_prefix = "doctest-7d42bd0fab6c44010c8aed9338bd02bea5feba41",
    )

    http_archive(
        name = "com_github_nelhage_rules_boost",
        urls = ["https://github.com/nelhage/rules_boost/archive/640eb2e2fd6b7bda2187af12b34df1ed01785789.zip"],
        sha256 = "335847417ad4ddae0831ec0e6e655d3e32915e9dca2af0d89295ebeefd6a9abe",
        strip_prefix = "rules_boost-640eb2e2fd6b7bda2187af12b34df1ed01785789",
    )
