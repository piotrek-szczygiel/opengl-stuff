add_requires("vcpkg::glfw3", {alias="glfw"})
add_requires("vcpkg::glad",  {alias="glad"})

target("opengl-stuff")
    set_kind("binary")
    add_files("src/*.cpp")
    add_packages("glfw", "glad")

    set_languages("c++17")
    set_warnings("all")
    set_rundir("$(projectdir)")

    if is_os("windows") then
        add_syslinks("user32", "gdi32", "shell32")
    end
