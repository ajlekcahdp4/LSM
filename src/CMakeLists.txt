
add_executable(calc ${CMAKE_CURRENT_SOURCE_DIR}/main.c)

set_target_properties(calc PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CALC_OUTPUT_DIR})


target_include_directories(calc PUBLIC ${LSM_INCLUDE_DIR})
target_link_libraries(calc lsm)