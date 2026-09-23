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

set(NDI_SDK_ROOT "$ENV{NDI_SDK_ROOT}" CACHE PATH "Path to the external NDI SDK")
find_path(NDI_INCLUDE_DIR Processing.NDI.Lib.h
    HINTS "${NDI_SDK_ROOT}/include"
)
find_library(NDI_LIBRARY NAMES ndi
    HINTS "${NDI_SDK_ROOT}/lib/${CMAKE_LIBRARY_ARCHITECTURE}"
          "${NDI_SDK_ROOT}/lib/${CMAKE_SYSTEM_PROCESSOR}-linux-gnu"
          "${NDI_SDK_ROOT}/lib"
)
if(NOT NDI_INCLUDE_DIR OR NOT NDI_LIBRARY)
    message(FATAL_ERROR "NDI SDK not found. Set NDI_SDK_ROOT, or NDI_INCLUDE_DIR and NDI_LIBRARY.")
endif()
target_include_directories(ndi2v4l2 SYSTEM PRIVATE "${NDI_INCLUDE_DIR}")
target_link_libraries(ndi2v4l2 PRIVATE "${NDI_LIBRARY}")
