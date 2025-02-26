enable_testing()
add_executable(${PROJECT_NAME}_tests)

target_include_directories(${PROJECT_NAME}_tests PRIVATE ${CMAKE_SOURCE_DIR}/cmocka/include)
target_link_directories(${PROJECT_NAME}_tests PRIVATE ${CMAKE_SOURCE_DIR}/cmocka/build/src)

target_compile_options(
    ${PROJECT_NAME}_tests
    PRIVATE
    -Wall
    -Werror
    -g
    -O0
)

target_compile_definitions(${PROJECT_NAME}_tests
    PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)


target_include_directories(${PROJECT_NAME}_tests PRIVATE ../include)
target_include_directories(${PROJECT_NAME}_tests PRIVATE include)

target_link_libraries(
    ${PROJECT_NAME}_tests
    cmocka
)

target_sources(${PROJECT_NAME}_tests PRIVATE ../src/example.c)

add_subdirectory(src)