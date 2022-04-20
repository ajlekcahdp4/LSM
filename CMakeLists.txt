cmake_minimum_required(VERSION 3.22)

project (LSM)

set (CMAKE_C_STANDARD 17)

add_compile_options(-Wall -Wextra)


add_library(lsm SHARED ${CMAKE_CURRENT_SOURCE_DIR}/sources/lsm/lsm.c)
target_sources(lsm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/SLE/SLE.c)
target_sources(lsm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/gnuplot/gnuplot.c)


target_include_directories(lsm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(lsm m)


add_executable(project ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.c)
target_include_directories(project PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(project lsm)
