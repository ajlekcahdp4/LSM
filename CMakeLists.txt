cmake_minimum_required(VERSION 3.9)

project (LSM)

add_compile_options(-Wall -Wextra)

include (lib/CMakeLists.txt)

add_executable(calc ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.c)
target_include_directories(calc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(calc lsm)
