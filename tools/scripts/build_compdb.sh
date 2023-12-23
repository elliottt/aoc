#!/usr/bin/env bash

set -euo pipefail

./tools/scripts/update_compdb_targets.sh

bazelisk run //:aoc_compdb
