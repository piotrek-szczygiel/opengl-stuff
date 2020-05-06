cmake_minimum_required(VERSION 3.1)

project(opengl-stuff)

add_subdirectory(deps/glfw EXCLUDE_FROM_ALL)
add_subdirectory(deps/glew EXCLUDE_FROM_ALL)
add_subdirectory(deps/glm  EXCLUDE_FROM_ALL)

# imgui source
file(GLOB IMGUI_SRC
    deps/imgui/*.cpp
    deps/imgui/examples/imgui_impl_glfw.cpp
    deps/imgui/examples/imgui_impl_opengl3.cpp
)

# main source
add_executable(main
  src/main.cpp

  ${IMGUI_SRC}
)

set_target_properties(main PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

target_compile_options(main PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -pedantic>
)

# imgui
target_include_directories(main PRIVATE deps/imgui deps/imgui/examples)

# glfw
target_link_libraries(main PRIVATE glfw)

# glew
target_compile_definitions(main PRIVATE -DGLEW_STATIC)
target_link_libraries(main PRIVATE libglew_static)

# glm
target_link_libraries(main PRIVATE glm)
