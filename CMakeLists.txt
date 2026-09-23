cmake_minimum_required(VERSION 3.16)

project(ndi2v4l2 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(ndi2v4l2 src/main.cpp)
set_target_properties(ndi2v4l2 PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
target_compile_definitions(ndi2v4l2 PRIVATE
    NDI2V4L2_VERSION="${PROJECT_VERSION}"
)
