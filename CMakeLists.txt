cmake_minimum_required(VERSION 3.22)

# { } OPTIONAL Change the project name to your challenge name
project(c_challenge 
    LANGUAGES C
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

add_executable(${PROJECT_NAME})

target_compile_options(${PROJECT_NAME} 
    PRIVATE
    -Wall
    -Werror
    $<$<CONFIG:Debug>:-g -O0>
)

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
)


target_include_directories(${PROJECT_NAME} PUBLIC include)

add_subdirectory(src)
add_subdirectory(tests)
