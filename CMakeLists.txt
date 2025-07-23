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

# INIT_TOOLS -> INIT_WINDOW:
    # GLFW
    FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw.git
            GIT_TAG        3.4
    )
    FetchContent_MakeAvailable(glfw)
    # ====
    # GLAD
    FetchContent_Declare(
            glad
            GIT_REPOSITORY https://github.com/Dav1dde/glad.git
            GIT_TAG        v0.1.36
    )
    if(NOT glad_POPULATED)
        FetchContent_GetProperties(glad)
        if(NOT glad_POPULATED)
            FetchContent_Populate(glad)

            set(GLAD_CMAKE_FILE "${glad_SOURCE_DIR}/CMakeLists.txt")
            file(READ "${GLAD_CMAKE_FILE}" GLAD_CMAKE_CONTENTS)
            string(REGEX REPLACE
                "cmake_minimum_required\\(VERSION[ \t]+3\\.0[^\)]*\\)"
                "cmake_minimum_required(VERSION 3.5)"
                GLAD_CMAKE_CONTENTS "${GLAD_CMAKE_CONTENTS}"
            )
            file(WRITE "${GLAD_CMAKE_FILE}" "${GLAD_CMAKE_CONTENTS}")
            
            add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})
        endif()
    endif()
    # ====
    # GLM
    FetchContent_Declare(
            glm
            GIT_REPOSITORY https://github.com/g-truc/glm.git
            GIT_TAG        1.0.1
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
target_link_libraries(InitTools PRIVATE
    spdlog # InitLogger
    glfw glad glm # InitWindow
)

target_compile_features(InitTools PUBLIC cxx_std_17)

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