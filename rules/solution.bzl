
def _aoc_solution_impl(ctx):

    runfiles = ctx.runfiles(files=[ctx.file.input] + ctx.files.binary)

    executable = ctx.actions.declare_file(ctx.label.name)

    ctx.actions.write(
        output=executable,
        content="{binary} {input}".format(
            binary = ctx.executable.binary.short_path,
            input = ctx.file.input.short_path,
        ),
        is_executable=True,
    )

    return [DefaultInfo(executable=executable, runfiles=runfiles)]

aoc_solution = rule(
    implementation = _aoc_solution_impl,
    attrs = {
        "binary": attr.label(
            cfg = "target",
            executable = True,
        ),
        "input": attr.label(
            allow_single_file = True,
        ),
    },
    executable = True,
)

def _solution_runner_impl(ctx):

    runfiles = ctx.runfiles()
    for solution in ctx.attr.solutions:
        info = solution[DefaultInfo]
        runfiles = runfiles.merge(info.default_runfiles)

    executable = ctx.actions.declare_file(ctx.label.name)

    ctx.actions.write(
        output=executable,
        content="\n".join([file.short_path for file in ctx.files.solutions]),
        is_executable=True,
    )

    return [DefaultInfo(executable=executable, runfiles=runfiles)]

_solution_runner = rule(
    implementation = _solution_runner_impl,
    attrs = {
        "solutions": attr.label_list()
    },
    executable = True,
)

def aoc_solutions(name, input=None, solutions=[]):
    sols=[]

    if input == None:
        sols=solutions
    else:
        for sol in solutions:
            sol_name = "{}-{}".format(name, sol)
            aoc_solution(
                name=sol_name,
                input=input,
                binary=sol,
            )
            sols.append(sol_name)

    _solution_runner(
        name=name,
        solutions=sols,
    )

def _solution_test_impl(ctx):

    ctx.actions.write(
        ctx.outputs.executable,
        content = """
        output="$(mktemp)"
        trap "rm $output" EXIT
        {solution} > "$output"
        solution="$(grep "{prefix}" "$output" | sed 's/{prefix}//')"
        if [[ "$solution" != "{expected}" ]]; then
          cat "$output"
          echo "==="
          echo "expected {expected}, but found $solution"
          exit 1
        fi
        """.format(
            solution = ctx.executable.solution.short_path,
            prefix = ctx.attr.prefix,
            expected = ctx.attr.expected,
        ),
        is_executable = True,
    )

    return [DefaultInfo(runfiles = ctx.attr.solution.default_runfiles)]


_solution_test = rule(
    test = True,
    implementation = _solution_test_impl,
    attrs = {
        "solution": attr.label(executable = True, cfg = "exec"),
        "prefix": attr.string(),
        "expected": attr.string(),
    }
)

def aoc_test(name, solution, result, expected, input=None):
    if input == None:
        sol = solution
    else:
        sol = "{}-{}".format(name, solution)
        aoc_solution(
            name = sol,
            input = input,
            binary = solution,
        )

    _solution_test(
        name = name,
        solution = sol,
        prefix = "{}: ".format(result),
        expected = expected,
    )

def aoc_tests(name, solution, spec, input=None):
    if input == None:
        sol = solution
    else:
        sol = "{}-{}".format(name, solution)
        aoc_solution(
            name = sol,
            input = input,
            binary = solution,
        )

    tests = []

    for i, k in enumerate(spec):
        i = i + 1
        test = "{}-{}".format(name, i)
        tests.append(test)
        aoc_test(
            name = test,
            solution = sol,
            result = k,
            expected = spec[k],
        )

    native.test_suite(
        name = name,
        tests = tests,
    )
