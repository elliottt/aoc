load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

HERMETIC_CC_TOOLCHAIN_VERSION = "v2.1.3"

def deps():
    http_archive(
        name = "range-v3",
        urls = ["https://github.com/ericniebler/range-v3/archive/0.12.0.tar.gz"],
        sha256 = "015adb2300a98edfceaf0725beec3337f542af4915cec4d0b89fa0886f4ba9cb",
        strip_prefix = "range-v3-0.12.0",
    )

    http_archive(
        name = "fmt",
        urls = ["https://github.com/fmtlib/fmt/archive/8.0.1.tar.gz"],
        sha256 = "b06ca3130158c625848f3fb7418f235155a4d389b2abc3a6245fb01cb0eb1e01",
        build_file = "//third_party:fmt.BUILD",
        strip_prefix = "fmt-8.0.1",
    )

    http_archive(
        name = "doctest",
        urls = ["https://github.com/doctest/doctest/archive/ae7a13539fb71f270b87eb2e874fbac80bc8dda2.zip"],
        sha256 = "ed32c51a7750d5996c7f8bc858890991be9e8153c37f9ad0c1418060ff894f72",
        strip_prefix = "doctest-ae7a13539fb71f270b87eb2e874fbac80bc8dda2",
    )

    http_archive(
        name = "com_github_nelhage_rules_boost",
        urls = ["https://github.com/nelhage/rules_boost/archive/96e9b631f104b43a53c21c87b01ac538ad6f3b48.tar.gz"],
        sha256 = "5ea00abc70cdf396a23fb53201db19ebce2837d28887a08544429d27783309ed",
        strip_prefix = "rules_boost-96e9b631f104b43a53c21c87b01ac538ad6f3b48",
    )

    http_archive(
        name = "json",
        urls = ["https://github.com/nlohmann/json/archive/db78ac1d7716f56fc9f1b030b715f872f93964e4.zip"],
        sha256 = "520907d368d32830771d1ed606821aa8a7501cbf7929b433c5ac0065027fa6e4",
        strip_prefix = "json-db78ac1d7716f56fc9f1b030b715f872f93964e4",
        build_file = "//third_party:json.BUILD",
    )

    http_archive(
        name = "hermetic_cc_toolchain",
        sha256 = "a5caccbf6d86d4f60afd45b541a05ca4cc3f5f523aec7d3f7711e584600fb075",
        urls = [
            "https://mirror.bazel.build/github.com/uber/hermetic_cc_toolchain/releases/download/{0}/hermetic_cc_toolchain-{0}.tar.gz".format(HERMETIC_CC_TOOLCHAIN_VERSION),
            "https://github.com/uber/hermetic_cc_toolchain/releases/download/{0}/hermetic_cc_toolchain-{0}.tar.gz".format(HERMETIC_CC_TOOLCHAIN_VERSION),
        ],
    )

    http_archive(
        name = "hedron_compile_commands",
        urls = ["https://github.com/hedronvision/bazel-compile-commands-extractor/archive/eac41eefb5c19d9a2d2bcdd60d6989660288333d.tar.gz"],
        strip_prefix = "bazel-compile-commands-extractor-eac41eefb5c19d9a2d2bcdd60d6989660288333d",
        sha256 = "716c149b5a2c4cdf8a80ecf6d59950b93366b2351ef868fb600c1d1963704b07",
    )
