cmake_minimum_required(VERSION 3.9)

project (lsm-lib)

set (LSM_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/lsm/lsm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/SLE/SLE.c
    ${CMAKE_CURRENT_SOURCE_DIR}/gnuplot/gnuplot.c
    ${CMAKE_CURRENT_SOURCE_DIR}/calcs/calcs.c
)

add_library(lsm SHARED ${LSM_SOURCES})

target_include_directories(lsm PUBLIC ${LSM_INCLUDE_DIR})
target_link_libraries(lsm m)
