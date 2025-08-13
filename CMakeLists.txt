cmake_minimum_required(VERSION 3.24)
project(InitTools VERSION 2.0.0 LANGUAGES CXX)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps -O2")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -fno-rtti")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Oz")
set(CMAKE_CXX_STANDARD 17)

message(STATUS "InitTools: Version ${PROJECT_VERSION}")
message(STATUS "InitTools: CMake CXX Standart ${CMAKE_CXX_STANDARD}")

#option(INITTOOLS_BUILD_DEBUG "InitTools Debug Build" OFF)
#if(INITTOOLS_BUILD_DEBUG)
#    message(STATUS "InitTools: Build Debug")
#    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
#else()
#    message(STATUS "InitTools: Build Release")
#    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
#endif()

# Порядок модулей:
# 1. InitPlatform
# 2. InitFiles
# 3. InitConsole
# 4. InitWindow

message(STATUS "InitTools: Build Type - ${CMAKE_BUILD_TYPE}")

option(INITTOOLS_ENABLE_INITPLATFORM "Enable Module InitPlatform" ON)
option(INITTOOLS_ENABLE_INITCONSOLE "Enable Module InitConsole" ON)
option(INITTOOLS_ENABLE_INITFILES "Enable Module InitFiles" ON)
option(INITTOOLS_ENABLE_INITWINDOW "Enable Module InitWindow" ON)

include(FetchContent)

message(STATUS "InitTools: INITTOOLS -> INITTOOLS")
# INIT_TOOLS -> INIT_TOOLS:
    file(GLOB_RECURSE INITTOOLS_SOURCES CONFIGURE_DEPENDS
        src/InitTools/InitTools/*.cpp
    )

if(INITTOOLS_ENABLE_INITPLATFORM)
message(STATUS "InitTools: INITTOOLS -> INITPLATFORM")
# INIT_TOOLS -> INIT_PLATFORM:
    message(STATUS "InitTools: INITTOOLS -> INITPLATFORM ~> WINDOWS")
    # INIT_TOOLS -> INIT_PLATFORM ~> WINDOWS:
        
    file(GLOB_RECURSE INITPLATFORM_SOURCES CONFIGURE_DEPENDS
        src/InitTools/InitPlatform/*.cpp
        src/InitTools/InitPlatform/InitPlatform_Windows/*.cpp
    )
else()
message(STATUS "InitTools: INITTOOLS_ENABLE_INITPLATFORM disabled")
endif()

if(INITTOOLS_ENABLE_INITFILES)
message(STATUS "InitTools: INITTOOLS -> INITFILES")
# INIT_TOOLS -> INIT_FILES:
    
    file(GLOB_RECURSE INITFILES_SOURCES CONFIGURE_DEPENDS
        src/InitTools/InitFiles/*.cpp
    )
else()
message(STATUS "InitTools: INITTOOLS_ENABLE_INITFILES disabled")
endif()

if(INITTOOLS_ENABLE_INITCONSOLE)
message(STATUS "InitTools: INITTOOLS -> INITCONSOLE")
# INIT_TOOLS -> INIT_CONSOLE:
    message(STATUS "InitTools: INITTOOLS -> INITCONSOLE ~> LOGGER")
    # INIT_TOOLS -> INIT_CONSOLE ~> LOGGER:
        message(STATUS "InitTools: INITTOOLS -> INITCONSOLE ~> LOGGER ~ spdlog v1.15.3")
        FetchContent_Declare( # spdlog
            spdlog
            GIT_REPOSITORY https://github.com/gabime/spdlog.git
            GIT_TAG        v1.15.3
        )
        FetchContent_MakeAvailable(spdlog)
    file(GLOB_RECURSE INITCONSOLE_SOURCES CONFIGURE_DEPENDS
        src/InitTools/InitConsole/*.cpp
        src/InitTools/InitConsole/InitConsole_Logger/*.cpp
    )
else()
message(STATUS "InitTools: INITTOOLS_ENABLE_INITCONSOLE disabled")
endif()

if(INITTOOLS_ENABLE_INITWINDOW)
message(STATUS "InitTools: INITTOOLS -> INITWINDOW")
# INIT_TOOLS -> INIT_WINDOW:
    # GLFW
    message(STATUS "InitTools: INITTOOLS -> INITWINDOW ~ GLFW 3.4")
    FetchContent_Declare(
            glfw
            GIT_REPOSITORY https://github.com/glfw/glfw.git
            GIT_TAG        3.4
    )
    FetchContent_MakeAvailable(glfw)
    # ====
    message(STATUS "InitTools: INITTOOLS -> INITWINDOW ~ GLAD v0.1.36")
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
    message(STATUS "InitTools: INITTOOLS -> INITWINDOW ~ GLM 1.0.1")
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
    file(GLOB_RECURSE INITWINDOW_SOURCES CONFIGURE_DEPENDS
        src/InitTools/InitWindow/*.cpp
    )
else()
message(STATUS "InitTools: INITTOOLS_ENABLE_INITWINDOW disabled")
endif()

# add_library
set(INITTOOLS_ADD_LIBRARY
    ${INITPLATFORM_SOURCES}
    ${INITCONSOLE_SOURCES}
    ${INITWINDOW_SOURCES}
)
if(INITTOOLS_ENABLE_INITPLATFORM) # InitPlatform
    list(APPEND INITTOOLS_ADD_LIBRARY ${INITPLATFORM_SOURCES})
endif()
if(INITTOOLS_ENABLE_INITCONSOLE) # InitConsole
    list(APPEND INITTOOLS_ADD_LIBRARY ${INITCONSOLE_SOURCES})
endif()
if(INITTOOLS_ENABLE_INITFILES) # InitFiles
    list(APPEND INITTOOLS_ADD_LIBRARY ${INITFILES_SOURCES})
endif()
if(INITTOOLS_ENABLE_INITWINDOW) # InitWindow
    list(APPEND INITTOOLS_ADD_LIBRARY ${INITWINDOW_SOURCES})
endif()

add_library(InitTools STATIC
    ${INITTOOLS_SOURCES}
    ${INITTOOLS_ADD_LIBRARY}
)
target_compile_features(InitTools PUBLIC cxx_std_20)

# target_link_libraries
set(INITTOOLS_TARGET_LINK_LIBRARIES)
if(INITTOOLS_ENABLE_INITPLATFORM) # InitPlatform

endif()
if(INITTOOLS_ENABLE_INITCONSOLE) # InitConsole
    list(APPEND INITTOOLS_TARGET_LINK_LIBRARIES spdlog)
endif()
if(INITTOOLS_ENABLE_INITFILES) # InitFiles

endif()
if(INITTOOLS_ENABLE_INITWINDOW) # InitWindow
    list(APPEND INITTOOLS_TARGET_LINK_LIBRARIES glfw glad glm)
endif()
target_link_libraries(InitTools PRIVATE
    ${INITTOOLS_TARGET_LINK_LIBRARIES}
)

# target_include_directories
set(INITTOOLS_TARGET_INCLUDE_DIRECTORIES)
if(INITTOOLS_ENABLE_INITPLATFORM) # InitPlatform

endif()
if(INITTOOLS_ENABLE_INITCONSOLE) # InitConsole
    list(APPEND INITTOOLS_TARGET_INCLUDE_DIRECTORIES ${spdlog_SOURCE_DIR}/include)
endif()
if(INITTOOLS_ENABLE_INITFILES) # InitFiles

endif()
if(INITTOOLS_ENABLE_INITWINDOW) # InitWindow
    list(APPEND INITTOOLS_TARGET_INCLUDE_DIRECTORIES ${glfw_SOURCE_DIR}/include ${glad_SOURCE_DIR}/include ${glm_SOURCE_DIR})
endif()
target_include_directories(InitTools
    PRIVATE
    ${INITTOOLS_TARGET_INCLUDE_DIRECTORIES}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_library(InitTools::InitTools ALIAS InitTools)
