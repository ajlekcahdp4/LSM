cmake_minimum_required(VERSION 3.9)

project (LSM)


set(LSM_BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LSM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CALC_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_compile_options(-Wall -Wextra)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/lsm)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

