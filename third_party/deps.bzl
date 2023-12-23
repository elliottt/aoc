load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def deps():
    http_archive(
        name = "range-v3",
        urls = ["https://github.com/ericniebler/range-v3/archive/0.12.0.tar.gz"],
        sha256 = "015adb2300a98edfceaf0725beec3337f542af4915cec4d0b89fa0886f4ba9cb",
        strip_prefix = "range-v3-0.12.0",
    )

    http_archive(
        name = "com_github_nelhage_rules_boost",
        urls = ["https://github.com/nelhage/rules_boost/archive/96e9b631f104b43a53c21c87b01ac538ad6f3b48.tar.gz"],
        sha256 = "5ea00abc70cdf396a23fb53201db19ebce2837d28887a08544429d27783309ed",
        strip_prefix = "rules_boost-96e9b631f104b43a53c21c87b01ac538ad6f3b48",
    )

    http_archive(
        name = "hedron_compile_commands",
        urls = ["https://github.com/hedronvision/bazel-compile-commands-extractor/archive/eac41eefb5c19d9a2d2bcdd60d6989660288333d.tar.gz"],
        strip_prefix = "bazel-compile-commands-extractor-eac41eefb5c19d9a2d2bcdd60d6989660288333d",
        sha256 = "716c149b5a2c4cdf8a80ecf6d59950b93366b2351ef868fb600c1d1963704b07",
    )
