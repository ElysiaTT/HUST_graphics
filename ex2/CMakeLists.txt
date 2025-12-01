cmake_minimum_required(VERSION 3.10)
project(SunEarthMoon)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 添加GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# 查找OpenGL
find_package(OpenGL REQUIRED)

# 包含第三方库
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

# 添加glad源文件
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# 主程序
add_executable(SunEarthMoon src/main.cpp)

target_include_directories(SunEarthMoon PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glm
)

target_link_libraries(SunEarthMoon
    glad
    glfw
    OpenGL::GL
)

# Windows特定设置
if(WIN32)
    set_target_properties(SunEarthMoon PROPERTIES
        WIN32_EXECUTABLE FALSE
    )
endif()

# 复制资源文件到输出目录
add_custom_command(TARGET SunEarthMoon POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/shaders
    COMMENT "Copying shaders to output directory"
)

add_custom_command(TARGET SunEarthMoon POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/textures
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/textures
    COMMENT "Copying textures to output directory"
)
