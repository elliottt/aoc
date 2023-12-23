load("@hedron_compile_commands//:refresh_compile_commands.bzl", "refresh_compile_commands")
load("//rules:compdb_targets.bzl", "TARGETS")

refresh_compile_commands(
    name = "aoc_compdb",
    targets = TARGETS,
    exclude_external_sources = True,
    exclude_headers = "external",
)
