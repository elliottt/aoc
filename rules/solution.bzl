
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

def _aoc_solutions_impl(ctx):

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

aoc_solutions = rule(
    implementation = _aoc_solutions_impl,
    attrs = {
        "solutions": attr.label_list()
    },
    executable = True,
)
