cmake_minimum_required(VERSION 3.24)
project(InitTools VERSION 1.0.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

message(STATUS "InitTools: Version 1.0.3")

option(INITTOOLS_BUILD_DEBUG "Дебаг билд" ON)

if(INITTOOLS_BUILD_DEBUG)
    message(STATUS "InitTools: Build Debug")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
else()
    message(STATUS "InitTools: Build Release")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

include(FetchContent)

# INIT_TOOLS -> INIT_LOGGER:
    message(STATUS "InitTools: INITTOOLS -> INIT_LOGGER ~ spdlog v1.15.3")
    FetchContent_Declare( # spdlog
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG        v1.15.3
    )
    FetchContent_MakeAvailable(spdlog)
    file(GLOB_RECURSE INIT_LOGGER_SOURCES CONFIGURE_DEPENDS
        src/InitTools/InitLogger/*.cpp
    )

# INIT_TOOLS -> INIT_WINDOW:
    # GLFW
    message(STATUS "InitTools: INITTOOLS -> INIT_WINDOW ~ GLFW 3.4")
    FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw.git
            GIT_TAG        3.4
    )
    FetchContent_MakeAvailable(glfw)
    # ====
    message(STATUS "InitTools: INITTOOLS -> INIT_WINDOW ~ GLAD v0.1.36")
    # GLAD - 
    set(GLAD_PATCH ${CMAKE_CURRENT_SOURCE_DIR}/patches/glad-set-min-cmake-3.24.patch)
    FetchContent_Declare(
            glad
            GIT_REPOSITORY https://github.com/Dav1dde/glad.git
            GIT_TAG        v0.1.36
            PATCH_COMMAND
                ${CMAKE_COMMAND} -E echo "Patching glad/CMakeLists.txt -> bump cmake_minimum_required to 3.24"
                COMMAND git apply ${GLAD_PATCH}
            UPDATE_DISCONNECTED 1
    )
    FetchContent_MakeAvailable(glad)
    # ====
    # GLM
    set(GLM_PATCH ${CMAKE_CURRENT_SOURCE_DIR}/patches/glm-set-min-cmake-3.24.patch)
    message(STATUS "InitTools: INITTOOLS -> INIT_WINDOW ~ GLM 1.0.1")
    FetchContent_Declare(
            glm
            GIT_REPOSITORY https://github.com/g-truc/glm.git
            GIT_TAG        1.0.1
            PATCH_COMMAND
                ${CMAKE_COMMAND} -E echo "Patching glm/CMakeLists.txt -> bump cmake_minimum_required to 3.24"
                COMMAND git apply ${GLM_PATCH}
            UPDATE_DISCONNECTED 1
    )
    FetchContent_MakeAvailable(glm)
    # ===
    find_package(OpenGL REQUIRED)
    file(GLOB_RECURSE INIT_WINDOW_SOURCES CONFIGURE_DEPENDS
        src/InitTools/InitWindow/*.cpp
    )

add_library(InitTools STATIC
    ${INIT_LOGGER_SOURCES}
    ${INIT_WINDOW_SOURCES}
)
target_compile_features(InitTools PUBLIC cxx_std_20)

target_link_libraries(InitTools PRIVATE
    spdlog # InitLogger
    glfw glad glm # InitWindow
)

target_include_directories(InitTools
    PRIVATE
        # InitLogger
        ${spdlog_SOURCE_DIR}/include
        # InitWindow
        ${glfw_SOURCE_DIR}/include
        ${glad_SOURCE_DIR}/include
        ${glm_SOURCE_DIR}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_library(InitTools::InitTools ALIAS InitTools)