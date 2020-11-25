load("//rules:solution.bzl", "aoc_solution", "aoc_solutions")

aoc_solutions(
    name = "day-5",
    solutions = [
        "solution-part-1",
        "solution-part-2",
    ],
)

cc_binary(
    name = "part-1",
    srcs = ["part-1.cc"],
    deps = ["@range-v3", "@fmt"],
    copts = ["-std=c++17"],
)

aoc_solution(
    name = "solution-part-1",
    binary = "part-1",
    input = "input.txt",
)

cc_binary(
    name = "part-2",
    srcs = ["part-2.cc"],
    deps = ["@range-v3", "@fmt"],
    copts = ["-std=c++17"],
)

aoc_solution(
    name = "solution-part-2",
    binary = "part-2",
    input = "input.txt",
)
