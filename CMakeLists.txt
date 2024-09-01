cmake_minimum_required(VERSION 3.0)
project(main)

set(CUDA_TOOLKIT_ROOT_DIR "/usr/local/cuda-12.5")
set(CMAKE_PREFIX_PATH "~/libtorch/share/cmake/Torch")

find_package(Torch REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(main main.cpp)
target_link_libraries(main "${TORCH_LIBRARIES}")
set_property(TARGET main PROPERTY CXX_STANDARD 17)
