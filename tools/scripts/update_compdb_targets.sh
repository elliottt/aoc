#!/usr/bin/env bash

set -euo pipefail

root="$(dirname "${BASH_SOURCE[0]}")/../.."

tmpfile=$(mktemp)

cat <<EOF > "$tmpfile"
# Automatically generated by //tools/scripts/update_compdb_targets.sh
TARGETS = [
EOF

bazelisk query 'kind("cc_(binary|library|test)", //...)' | \
  sort | \
  while read target; do
    echo "  '${target}'," >> "$tmpfile"
  done

echo "]" >> "$tmpfile"

mv "$tmpfile" "$root/rules/compdb_targets.bzl"
