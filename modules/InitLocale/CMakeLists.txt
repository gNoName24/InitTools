cmake_minimum_required(VERSION 3.24)
project(InitLocale)
project_message(STATUS "Add module .cpp files")
add_library(InitLocale
    src/InitLocale.cpp
    src/InitLocale/LocaleManager.cpp

    # MoParser
    src/MoParser/MoParser.cpp
)
set_target_properties(InitLocale PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

project_message(STATUS "Add module includes")
target_include_directories(InitLocale PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
