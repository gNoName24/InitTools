cmake_minimum_required(VERSION 3.24)
project(InitConsole)

# Зависимости:
# Нету

project_message(STATUS "Add module .cpp files")
add_library(InitConsole
    src/InitConsole.cpp
    src/InitConsole/Logger.cpp
)
set_target_properties(InitConsole PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

project_message(STATUS "Add compile definitions")
target_compile_definitions(InitConsole PUBLIC
    BUILD_TYPE_STR=\"${CMAKE_BUILD_TYPE}\"
)

project_message(STATUS "Add module includes")
target_include_directories(InitConsole PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
