load("@com_grail_bazel_compdb//:aspects.bzl", "compilation_database")
load("//rules:compdb_targets.bzl", "TARGETS")

compilation_database(
    name = "aoc_compdb",
    targets = TARGETS,
    visibility = ["//visibility:public"],
    testonly = True,
)
