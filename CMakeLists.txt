cmake_minimum_required(VERSION 3.14)
project(InitLogger VERSION 1.0.0 LANGUAGES CXX)

# FetchContent
include(FetchContent)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG        v1.15.3
)
FetchContent_MakeAvailable(spdlog)

add_library(InitLogger STATIC
    src/InitLogger.cpp
)

target_include_directories(InitLogger
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(InitLogger PUBLIC cxx_std_17)
target_link_libraries(InitLogger PUBLIC spdlog)

add_library(InitLogger::InitLogger ALIAS InitLogger)