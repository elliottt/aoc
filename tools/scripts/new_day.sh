#!/usr/bin/env bash

set -euo pipefail


year=${1}
day=${2}

if [ -z "${year}" ] || [ -z "${day}" ]; then
  cat << EOF
Usage: ./tools/scripts/new_day.sh <year> <day>
EOF
exit 1
fi

root="$(dirname "${BASH_SOURCE[0]}")/../.."

solution="${root}/${year}/day-${day}"

if [ -d "${solution}" ]; then
  echo "solution already exists in ${solution}!"
  exit 1
fi

mkdir -p "${solution}"

cat << EOF > "${solution}/BUILD"
load("//rules:solution.bzl", "aoc_solutions", "aoc_tests")
load("//rules:config.bzl", "COPTS")

aoc_solutions(
    name = "day-${day}",
    input = "input.txt",
    solutions = [ "solution" ],
)

# aoc_tests(
#     name = "test",
#     input = "test.txt",
#     solution = "solution",
#     spec = {
#     },
# )

cc_binary(
    name = "solution",
    srcs = ["solution.cc"],
    deps = ["//common", "@range-v3", "@fmt"],
    copts = COPTS,
    visibility = ["//visibility:public"],
)
EOF

cat << EOF > "${solution}/solution.cc"
#include <fstream>
#include <range/v3/all.hpp>
#include <fmt/format.h>
#include <vector>
#include <string>

namespace views = ranges::views;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 0;
    }

    return 0;
}
EOF

"${root}/tools/scripts/build_compdb.sh"
