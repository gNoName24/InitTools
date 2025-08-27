cmake_minimum_required(VERSION 3.24)
project(InitWindow)

# Зависимости:
# GLFW

include(FetchContent)

project_message(STATUS "Add module .cpp files")
add_library(InitWindow
    src/InitWindow.cpp

    # Class WindowManager
    src/InitWindow/WindowManager.cpp
    src/InitWindow/WindowManager/Callbacks.cpp
    src/InitWindow/WindowManager/Set-Get.cpp
)
set_target_properties(InitWindow PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# INCLUDE LIBRARIES
project_message(STATUS "Include library: GLFW")
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.4
)
FetchContent_MakeAvailable(glfw)

project_message(STATUS "Include library: GLAD")
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

project_message(STATUS "Include library: GLM")
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
# #################

project_message(STATUS "Add module includes")
target_include_directories(InitWindow PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# LINK LIBRARIES
project_message(STATUS "Link library: GLFW")
target_link_libraries(InitWindow PUBLIC glfw)

project_message(STATUS "Link library: GLAD")
target_link_libraries(InitWindow PUBLIC glad)

project_message(STATUS "Link library: GLM")
target_link_libraries(InitWindow PUBLIC glm)
# ##############
