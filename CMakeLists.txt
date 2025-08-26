cmake_minimum_required(VERSION 3.24)
project(InitTools VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(INITTOOLS_PROJECT_MESSAGE_MODULE OFF)
function(project_message msg_type msg_text)
    if(INITTOOLS_PROJECT_MESSAGE_MODULE)
        message(${msg_type} "[InitTools] [${PROJECT_NAME}] ${msg_text}")
    else()
        message(${msg_type} "[InitTools] ${msg_text}")
    endif()
endfunction()

set(PROJECT_RELEASE false)
set(PROJECT_PRERELEASE "beta.2")
set(PROJECT_FULL_VERSION "${PROJECT_VERSION}")
if(NOT PROJECT_RELEASE)
    set(PROJECT_FULL_VERSION "${PROJECT_VERSION}-${PROJECT_PRERELEASE}")
    project_message(STATUS "The current version ${PROJECT_FULL_VERSION} is not a release version. Use this version at your own risk.")
endif()

set(INITTOOLS_VERSION ${PROJECT_VERSION})
set(INITTOOLS_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(INITTOOLS_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(INITTOOLS_VERSION_PATCH ${PROJECT_VERSION_PATCH})

# INITTOOLS_RELEASE - true / false
# INITTOOLS_VERSION_MAJOR/MINOR/PATCH - x
# INITTOOLS_VERSION - x.x.x
# INITTOOLS_PRERELEASE - pr.x
# INITTOOLS_FULL_VERSION - x.x.x.-pr.x

# 1. InitConsole
project_message(STATUS ">InitConsole<")
set(INITTOOLS_PROJECT_MESSAGE_MODULE ON)
    add_subdirectory(modules/InitConsole)
set(INITTOOLS_PROJECT_MESSAGE_MODULE OFF)

# 2. InitLocale
project_message(STATUS ">InitLocale<")
set(INITTOOLS_PROJECT_MESSAGE_MODULE ON)
    add_subdirectory(modules/InitLocale)
set(INITTOOLS_PROJECT_MESSAGE_MODULE OFF)


# Тестирование
include(CTest)
enable_testing()

add_executable(InitToolsTests tests/main.cpp)
target_link_libraries(InitToolsTests PRIVATE InitConsole)
target_link_libraries(InitToolsTests PRIVATE InitLocale)
add_test(NAME InitToolsTests_main COMMAND InitToolsTests)
