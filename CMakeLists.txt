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
add_subdirectory(external/glfw)
target_link_libraries(MyRenderingEngine PRIVATE glfw)

# Vulkan #
find_package(Vulkan REQUIRED)
target_include_directories(MyRenderingEngine PRIVATE ${Vulkan_INCLUDE_DIRS})
message(${Vulkan_INCLUDE_DIRS})
target_link_libraries(MyRenderingEngine PRIVATE ${Vulkan_LIBRARIES})
message(${Vulkan_LIBRARIES})
