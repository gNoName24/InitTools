cmake_minimum_required(VERSION 3.14)
project(InitTools VERSION 1.0.0 LANGUAGES CXX)

# set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)

include(FetchContent)

# INIT_TOOLS -> INIT_LOGGER:
    FetchContent_Declare( # spdlog
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG        v1.15.3
    )
    FetchContent_MakeAvailable(spdlog)
    file(GLOB_RECURSE INIT_LOGGER_SOURCES CONFIGURE_DEPENDS
        src/InitTools/InitLogger/*.cpp
    )
    add_library(InitTools STATIC ${INIT_LOGGER_SOURCES})
    target_link_libraries(InitTools PUBLIC spdlog)
    
target_compile_features(InitTools PUBLIC cxx_std_17)

target_include_directories(InitTools
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_library(InitTools::InitTools ALIAS InitTools)