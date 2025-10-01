cmake_minimum_required(VERSION 3.10)

project(AgonyAndPain VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/libs)
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/libs/third_party)

# dependencies
# GLAD validation
if(NOT EXISTS ${CMAKE_SOURCE_DIR}/libs/glad/src/glad.c)
    message(WARNING "GLAD not found. Download from https://glad.dav1d.de (API: Core, Profile: Core, Version: 4.6)")
    message(FATAL_ERROR "GLAD required in libs/glad/")
endif()

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG master
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/glfw
)
# GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG master
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/glm
)
# third party
# stb_image.h
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/third_party/stb
)
# ImGUI
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG master
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/imgui
)
FetchContent_MakeAvailable(glfw glm stb imgui)

# Library targets
# GLAD (local loader)
add_library(glad STATIC ${CMAKE_SOURCE_DIR}/libs/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/libs/glad/include)

# stb
add_library(stb_image INTERFACE)
target_include_directories(stb_image INTERFACE ${stb_SOURCE_DIR})

#imgui
add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC 
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
    ${glfw_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/libs/glad/include
)
target_compile_definitions(imgui PRIVATE IMGUI_IMPL_OPENGL_LOADER_GLAD)

find_package(OpenGL REQUIRED)

file (GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${PROJECT_NAME} PRIVATE 
    glad
    glfw
    glm
    stb_image
    imgui
    OpenGL::GL
)

# on linux
if (UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE dl pthread X11)
elseif(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE opengl32)
endif()

# runtime resources
file(COPY ${CMAKE_SOURCE_DIR}/resources ${CMAKE_SOURCE_DIR}/config DESTINATION ${CMAKE_CURRENT_BINARY_DIR})