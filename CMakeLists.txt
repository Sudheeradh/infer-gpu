# Specify the minimum CMake version required
cmake_minimum_required(VERSION 3.15)

# Set the project name and programming language
project(MyInferProject VERSION 1.0 LANGUAGES CXX CUDA)

find_package(CUDAToolkit REQUIRED)

# Require C++17 standard
set(CMAKE_CXX_STANDARD 17)

# Define an executable target: output_executable_name source_files...
add_executable(my_app src/main.cpp)
target_include_directories(my_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(my_app PRIVATE
    CUDA::cublas
    CUDA::cudart
)