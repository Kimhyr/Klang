add_rules("mode.debug", "mode.release")

set_languages("c++20")
set_warnings("allextra")
set_toolchains("clang")
add_includedirs(".", "include")
-- add_cxxflags("-mavx -mavx2")

if is_mode("debug") then
    set_symbols("debug")
    set_optimize("none")
elseif is_mode("release") then
    set_symbols("hidden")
    set_optimize("fast")
    set_strip("all")
end

target("hack", {
    kind = "binary",
    files = "klang/**.cpp",
    pcxxheader = "klang/precompile.h",
})
