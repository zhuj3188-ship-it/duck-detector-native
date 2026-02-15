cmake_minimum_required(VERSION 3.22.1)

project("duckdetector")

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler flags
add_compile_options(-Wall -Wextra -Werror -fvisibility=hidden)

# Find required libraries
find_library(log-lib log)
find_library(android-lib android)

# Create native library
add_library(duckdetector SHARED
        native_detector.cpp
        selinux_detector.cpp
        kernel_detector.cpp
        mount_detector.cpp
        zygisk_detector.cpp
        heap_detector.cpp
        filesystem_detector.cpp
        preload_detector.cpp
        jni_bridge.cpp
)

# Link libraries
target_link_libraries(duckdetector
        ${log-lib}
        ${android-lib}
)
