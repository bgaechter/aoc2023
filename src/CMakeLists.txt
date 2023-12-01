file(GLOB_RECURSE aoc2023_SRC
    "**/*.h"
    "**/*.cpp"
    "*.cpp"
    "*.h"
)

include_directories("${CMAKE_SOURCE_DIR}/src")

add_executable(aoc2023 ${aoc2023_SRC})
