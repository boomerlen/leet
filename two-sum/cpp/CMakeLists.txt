cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(TwoSumCPP VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

cmake_policy(SET CMP0076 NEW)

# Create compile_commands.json for better IDE support
# https://stackoverflow.com/questions/59263015/cmake-how-to-change-compile-commands-json-output-location
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
if (PROJECT_IS_TOP_LEVEL AND UNIX)
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E create_symlink 
            ${CMAKE_BINARY_DIR}/compile_commands.json 
            ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
        )
endif()

add_executable(app
    src/main.cpp
    src/TwoSumAccelerated.cpp
    src/TwoSumNative.cpp
)

# Options
# Some macro to simplify this?
option(MODE_TIMED "Whether to perform repeated executions and time results" OFF)
if(${MODE_TIMED})
    add_compile_definitions(MODE_TIMED)
endif()

option(MODE_TIMED_N "Number of repetitions to perform during timed execution" 1000)
add_compile_definitions(MODE_TIMED_N ${MODE_TIMED_N})

option(CSV_BUFLEN "Maximum line length of CSV input file to allow for" 2048)
add_compile_definitions(CSV_BUFLEN ${CSV_BUFLEN})

option(RUNNER_GPU "Whether to use GPU accelerated operation" OFF)
if(${RUNNER_GPU})
    add_compile_definitions(RUNNER_GPU)
    target_sources(app PUBLIC src/TwoSumAccelerated.cpp)
else()
    target_sources(app PUBLIC src/TwoSumNative.cpp src/Tree.cpp)
endif()


include_directories(app include)

install(TARGETS app RUNTIME DESTINATION bin)
