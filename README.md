# Advent of Code Solutions

## Building

This assumes a working C++20 compiler. On WSL with Ubuntu, I set the CC
environment variable to `clang`.

## Running a solution

Each directory has a rule with the same name, so you can just use `bazel run` to
run both parts of the solution.

```
CC=clang bazel run -c opt 2020/day-1
```
