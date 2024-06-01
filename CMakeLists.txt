cmake_minimum_required(VERSION 3.28)
project(MyRenderingEngine)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS src/*)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE src)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# GLFW #
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_library(glfw INTERFACE)

# FMT #
add_subdirectory(./external/fmt)
set(FMT_INSTALL ON CACHE BOOL "" FORCE)
set(FMT_CUDA_TEST ON CACHE BOOL "" FORCE)
set(FMT_SYSTEM_HEADERS ON CACHE BOOL "" FORCE)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

# FastGLTF #
add_subdirectory(./external/fastgltf)
target_link_libraries(${PROJECT_NAME} PRIVATE fastgltf)

# STB #
target_include_directories(${PROJECT_NAME} PRIVATE ./external/stb_image)

# Vulkan #
find_package(Vulkan REQUIRED)

add_library(glm INTERFACE)
target_include_directories(glm INTERFACE $ENV{VULKAN_SDK}/Include/vma)
target_link_directories(glm INTERFACE $ENV{VULKAN_SDK}/Lib)

add_library(vma INTERFACE)
target_include_directories(vma INTERFACE $ENV{VULKAN_SDK}/Include/vma)
target_link_directories(vma INTERFACE $ENV{VULKAN_SDK}/Lib)

add_library(sdl2 INTERFACE)
target_include_directories(sdl2 INTERFACE $ENV{VULKAN_SDK}/Include/SDL2 )
target_link_directories(sdl2 INTERFACE $ENV{VULKAN_SDK}/Lib )

target_link_libraries(sdl2 INTERFACE SDL2 SDL2main)

target_include_directories(${PROJECT_NAME} PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${Vulkan_LIBRARIES})

find_program(GLSL_VALIDATOR glslangValidator HINTS /usr/bin /usr/local/bin $ENV{VULKAN_SDK}/Bin/ $ENV{VULKAN_SDK}/Bin32/)

add_subdirectory(./external/vkbootstrap)
target_link_libraries(${PROJECT_NAME} PRIVATE vk-bootstrap)

# ImGUI #
add_library(ImGui)
target_compile_features(ImGui PUBLIC cxx_std_11)

if (WIN32)
    target_link_libraries(ImGui PRIVATE imm32) # Required only when using mingw, not Visual Studio
endif()

target_include_directories(ImGui PUBLIC ./external/imgui)
target_sources(ImGui PRIVATE
        ./external/imgui/imgui.cpp
        ./external/imgui/imgui_demo.cpp
        ./external/imgui/imgui_draw.cpp
        ./external/imgui/imgui_tables.cpp
        ./external/imgui/imgui_widgets.cpp
        ./external/imgui/misc/cpp/imgui_stdlib.cpp
        ./external/imgui/backends/imgui_impl_vulkan.cpp
        ./external/imgui/backends/imgui_impl_sdl2.cpp
)
target_include_directories(ImGui PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(ImGui PRIVATE ${Vulkan_LIBRARIES})
target_link_libraries(ImGui PRIVATE sdl2)
target_link_libraries(${PROJECT_NAME} PRIVATE ImGui)

# GLSL #
file(GLOB_RECURSE GLSL_SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/shaders/*.frag"
        "${PROJECT_SOURCE_DIR}/shaders/*.vert"
        "${PROJECT_SOURCE_DIR}/shaders/*.comp"
)

foreach(GLSL ${GLSL_SOURCE_FILES})
    message(STATUS "BUILDING SHADER")
    get_filename_component(FILE_NAME ${GLSL} NAME)
    set(SPIRV "${PROJECT_SOURCE_DIR}/shaders/${FILE_NAME}.spv")
    message(STATUS ${GLSL})
    add_custom_command(
            OUTPUT ${SPIRV}
            COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
            DEPENDS ${GLSL})
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
        Shaders
        DEPENDS ${SPIRV_BINARY_FILES}
)