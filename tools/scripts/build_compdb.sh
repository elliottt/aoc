#!/usr/bin/env bash

set -euo pipefail

./tools/scripts/update_compdb_targets.sh

root="$(dirname "${BASH_SOURCE[0]}")/../.."

outfile="$(bazelisk info bazel-bin)/compile_commands.json"
execroot="$(bazelisk info execution_root)"

bazelisk build //:aoc_compdb

sed "s|__EXEC_ROOT__|${execroot}|" "$outfile" > "$root/compile_commands.json"
