cmake_minimum_required(VERSION 3.24)
project(InitTools VERSION 2.0.0 LANGUAGES CXX)

# add_compile_options(-save-temps=obj -dumpdir ${CMAKE_BINARY_DIR}/clang_temps/)

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
# 1. InitLocale
# 2. InitPlatform
# 3. InitFiles
# 4. InitConsole
# 5. InitWindow

message(STATUS "InitTools: Build Type - ${CMAKE_BUILD_TYPE}")

# Включение / Выключение модулей
option(INITTOOLS_ENABLE_INITLOCALE "Enable Module InitLocale" ON)
option(INITTOOLS_ENABLE_INITPLATFORM "Enable Module InitPlatform" ON)
option(INITTOOLS_ENABLE_INITCONSOLE "Enable Module InitConsole" ON)
option(INITTOOLS_ENABLE_INITFILES "Enable Module InitFiles" ON)
option(INITTOOLS_ENABLE_INITWINDOW "Enable Module InitWindow" ON)

# Использование внешних библиотек для этой библиотеки
option(INITTOOLS_USE_SYSTEM_SPDLOG "Use system spdlog instead of FetchContent" OFF)
option(INITTOOLS_USE_SYSTEM_GLFW "Use system glfw instead of FetchContent" OFF)
option(INITTOOLS_USE_SYSTEM_GLAD "Use system glad instead of FetchContent" OFF)
option(INITTOOLS_USE_SYSTEM_GLM "Use system glm instead of FetchContent" OFF)

include(FetchContent)

# MoParser (https://github.com/laurent22/simple-gettext)
file(GLOB_RECURSE MOPARSER_SOURCES CONFIGURE_DEPENDS
    src/MoParser/*.cpp
)

message(STATUS "InitTools: INITTOOLS -> INITTOOLS")
# INIT_TOOLS -> INIT_TOOLS:
    file(GLOB_RECURSE INITTOOLS_SOURCES CONFIGURE_DEPENDS
        src/InitTools/InitTools/*.cpp
    )

if(INITTOOLS_ENABLE_INITLOCALE)
message(STATUS "InitTools: INITTOOLS -> INITLOCALE")
# INIT_TOOLS -> INIT_LOCALE:

    file(GLOB_RECURSE INITLOCALE_SOURCES CONFIGURE_DEPENDS
        src/InitTools/InitLocale/*.cpp
    )
else()
message(STATUS "InitTools: INITTOOLS_ENABLE_INITLOCALE disabled")
endif()

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
        # spdlog
        message(STATUS "InitTools: INITTOOLS -> INITCONSOLE ~> LOGGER ~ spdlog v1.15.3 (USE_SYSTEM: ${INITTOOLS_USE_SYSTEM_SPDLOG})")
        if(INITTOOLS_USE_SYSTEM_SPDLOG)
            find_package(spdlog REQUIRED)
        else()
            FetchContent_Declare(
                spdlog
                GIT_REPOSITORY https://github.com/gabime/spdlog.git
                GIT_TAG        v1.15.3
            )
            FetchContent_MakeAvailable(spdlog)
        endif()
        # ===========================================================================================================================
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
        message(STATUS "InitTools: INITTOOLS -> INITWINDOW ~ GLFW 3.4 (USE_SYSTEM: ${INITTOOLS_USE_SYSTEM_GLFW})")
        if(INITTOOLS_USE_SYSTEM_GLFW)
            if(GLFW3_LIBRARY AND GLFW3_INCLUDE_DIR)
                # message(STATUS "Using manually provided GLFW: ${GLFW3_LIBRARY}")
                set(GLFW_LIBRARIES ${GLFW3_LIBRARY})
                set(GLFW_INCLUDE_DIRS ${GLFW3_INCLUDE_DIR})
            else()
                find_package(glfw REQUIRED)
            endif()
        else()
            FetchContent_Declare(
                glfw
                GIT_REPOSITORY https://github.com/glfw/glfw.git
                GIT_TAG        3.4
            )
            FetchContent_MakeAvailable(glfw)
        endif()
        # ========================================================================================================
        # GLAD
        message(STATUS "InitTools: INITTOOLS -> INITWINDOW ~ GLAD v0.1.36 (USE_SYSTEM: ${INITTOOLS_USE_SYSTEM_GLAD})")
        if(INITTOOLS_USE_SYSTEM_GLAD)
            find_package(glad REQUIRED)
        else()
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
        endif()
        FetchContent_MakeAvailable(glad)
        # ============================================================================================================
        # GLM
        message(STATUS "InitTools: INITTOOLS -> INITWINDOW ~ GLM 1.0.1 (USE_SYSTEM: ${INITTOOLS_USE_SYSTEM_GLM})")
        if(INITTOOLS_USE_SYSTEM_GLM)
            find_package(glm REQUIRED)
        else()
            set(GLM_PATCH ${CMAKE_CURRENT_SOURCE_DIR}/patches/glm-set-min-cmake-3.24.patch)
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
        endif()
        # ========================================================================================================
    find_package(OpenGL REQUIRED)
    file(GLOB_RECURSE INITWINDOW_SOURCES CONFIGURE_DEPENDS
        src/InitTools/InitWindow/*.cpp
    )
else()
message(STATUS "InitTools: INITTOOLS_ENABLE_INITWINDOW disabled")
endif()

# add_library
set(INITTOOLS_ADD_LIBRARY
    ${INITLOCALE_SOURCES}
    ${INITPLATFORM_SOURCES}
    ${INITFILES_SOURCES}
    ${INITCONSOLE_SOURCES}
    ${INITWINDOW_SOURCES}
)
if(INITTOOLS_ENABLE_INITLOCALE) # InitLocale
    list(APPEND INITTOOLS_ADD_LIBRARY ${INITLOCALESOURCES})
endif()
if(INITTOOLS_ENABLE_INITPLATFORM) # InitPlatform
    list(APPEND INITTOOLS_ADD_LIBRARY ${INITPLATFORM_SOURCES})
endif()
if(INITTOOLS_ENABLE_INITFILES) # InitFiles
    list(APPEND INITTOOLS_ADD_LIBRARY ${INITFILES_SOURCES})
endif()
if(INITTOOLS_ENABLE_INITCONSOLE) # InitConsole
    list(APPEND INITTOOLS_ADD_LIBRARY ${INITCONSOLE_SOURCES})
endif()
if(INITTOOLS_ENABLE_INITWINDOW) # InitWindow
    list(APPEND INITTOOLS_ADD_LIBRARY ${INITWINDOW_SOURCES})
endif()

add_library(InitTools STATIC
    ${MOPARSER_SOURCES}
    ${INITTOOLS_SOURCES}
    ${INITTOOLS_ADD_LIBRARY}
)
target_compile_features(InitTools PUBLIC cxx_std_20)

# target_link_libraries
set(INITTOOLS_TARGET_LINK_LIBRARIES)
if(INITTOOLS_ENABLE_INITLOCALE) # InitLocale

endif()
if(INITTOOLS_ENABLE_INITPLATFORM) # InitPlatform

endif()
if(INITTOOLS_ENABLE_INITFILES) # InitFiles

endif()
if(INITTOOLS_ENABLE_INITCONSOLE) # InitConsole
    list(APPEND INITTOOLS_TARGET_LINK_LIBRARIES spdlog)
endif()
if(INITTOOLS_ENABLE_INITWINDOW) # InitWindow
    list(APPEND INITTOOLS_TARGET_LINK_LIBRARIES glfw glad glm)
endif()
target_link_libraries(InitTools PUBLIC
    ${INITTOOLS_TARGET_LINK_LIBRARIES}
)

# target_include_directories
set(INITTOOLS_TARGET_INCLUDE_DIRECTORIES)
if(INITTOOLS_ENABLE_INITLOCALE) # InitLocale

endif()
if(INITTOOLS_ENABLE_INITPLATFORM) # InitPlatform

endif()
if(INITTOOLS_ENABLE_INITFILES) # InitFiles

endif()
if(INITTOOLS_ENABLE_INITCONSOLE) # InitConsole
    list(APPEND INITTOOLS_TARGET_INCLUDE_DIRECTORIES ${spdlog_SOURCE_DIR}/include)
endif()
if(INITTOOLS_ENABLE_INITWINDOW) # InitWindow
    list(APPEND INITTOOLS_TARGET_INCLUDE_DIRECTORIES ${glfw_SOURCE_DIR}/include ${glad_SOURCE_DIR}/include ${glm_SOURCE_DIR})
endif()
target_include_directories(InitTools
    PUBLIC
        ${INITTOOLS_TARGET_INCLUDE_DIRECTORIES}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

add_library(InitTools::InitTools ALIAS InitTools)

# Тестирование
#enable_testing()

#file(GLOB INITTOOLS_TEST_SOURCES CONFIGURE_DEPENDS tests/*.cpp)

#foreach(test_file IN LISTS INITTOOLS_TEST_SOURCES)
#    get_filename_component(test_name ${test_file} NAME_WE)

#    add_executable(${test_name} ${test_file})
#    target_link_libraries(${test_name} PRIVATE InitTools)

#    add_test(NAME ${test_name} COMMAND ${test_name})

    # target_compile_options(${test_name} PRIVATE -Os -ffunction-sections -fdata-sections -flto)
    # target_link_options(${test_name} PRIVATE -Wl,--gc-sections -s -flto)
#endforeach()
