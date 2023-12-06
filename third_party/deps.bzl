load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

HERMETIC_CC_TOOLCHAIN_VERSION = "v2.0.0-rc2"

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
        urls = ["https://github.com/onqtam/doctest/archive/7d42bd0fab6c44010c8aed9338bd02bea5feba41.zip"],
        sha256 = "b33c8e954d15a146bb744ca29f4ca204b955530f52b2f8a895746a99cee4f2df",
        build_file = "//third_party:doctest.BUILD",
        strip_prefix = "doctest-7d42bd0fab6c44010c8aed9338bd02bea5feba41",
    )

    http_archive(
        name = "com_github_nelhage_rules_boost",
        urls = ["https://github.com/nelhage/rules_boost/archive/96e9b631f104b43a53c21c87b01ac538ad6f3b48.tar.gz"],
        sha256 = "5ea00abc70cdf396a23fb53201db19ebce2837d28887a08544429d27783309ed",
        strip_prefix = "rules_boost-96e9b631f104b43a53c21c87b01ac538ad6f3b48",
    )

    http_archive(
        name = "com_grail_bazel_compdb",
        urls = ["https://github.com/grailbio/bazel-compilation-database/archive/0ae6349c52700f060c9a87c5ed2b04b75f94a26f.zip"],
        sha256 = "40ad122fedbf2d8b23e70e16b5f49c1a316f02db3ed29ce1af8650dad6ccc1a9",
        strip_prefix = "bazel-compilation-database-0ae6349c52700f060c9a87c5ed2b04b75f94a26f",
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
        sha256 = "40dff82816735e631e8bd51ede3af1c4ed1ad4646928ffb6a0e53e228e55738c",
        urls = [
            "https://mirror.bazel.build/github.com/uber/hermetic_cc_toolchain/releases/download/{0}/hermetic_cc_toolchain-{0}.tar.gz".format(HERMETIC_CC_TOOLCHAIN_VERSION),
            "https://github.com/uber/hermetic_cc_toolchain/releases/download/{0}/hermetic_cc_toolchain-{0}.tar.gz".format(HERMETIC_CC_TOOLCHAIN_VERSION),
        ],
    )
