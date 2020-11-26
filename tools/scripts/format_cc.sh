#!/usr/bin/env bash

set -euo pipefail

root="$(dirname "${BASH_SOURCE[0]}")/../.."

format_file() {
  formatted="$1.formatted"
  clang-format "$1" > "$formatted"
  if cmp -s "$1" "$formatted"; then
    rm "$formatted"
  else
    echo "$1"
    mv "$formatted" "$1"
  fi
}

git ls-files | \
  grep -E '\.(cc|h)$' | \
  grep -v third_party | \
  while read source_file; do
    format_file "$root/$source_file"
  done
