{
    files = {
        "klang/main.cpp",
        "build/.objs/hack/linux/x86_64/release/klang/cxx/precompile.h.pch"
    },
    depfiles_gcc = "build/.objs/hack/linux/x86_64/release/klang/__cpp_main.cpp.cpp:   klang/main.cpp /home/king/Projects/klang/klang/precompile.h   klang/lexer.h klang/precompile.h\
",
    values = {
        "/usr/bin/clang",
        {
            "-Qunused-arguments",
            "-m64",
            "-fvisibility=hidden",
            "-fvisibility-inlines-hidden",
            "-Wall",
            "-Wextra",
            "-O1",
            "-std=c++20",
            "-I.",
            "-include",
            "klang/precompile.h",
            "-include-pch",
            "build/.objs/hack/linux/x86_64/release/klang/cxx/precompile.h.pch",
            "-DNDEBUG"
        }
    }
}