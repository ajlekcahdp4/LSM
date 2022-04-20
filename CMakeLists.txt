cmake_minimum_required(VERSION 3.9)

project (LSM)

add_library(lsm SHARED ${CMAKE_CURRENT_SOURCE_DIR}/sources/lsm/lsm.c)
target_sources(lsm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/SLE/SLE.c)
target_sources(lsm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/sources/gnuplot/gnuplot.c)


target_include_directories(lsm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(lsm m)

add_executable(calc ${CMAKE_CURRENT_SOURCE_DIR}/sources/main.c)
target_include_directories(calc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(calc lsm)
