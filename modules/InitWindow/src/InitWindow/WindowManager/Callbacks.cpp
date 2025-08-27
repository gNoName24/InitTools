// Namespace InitWindow -> Segment Callbacks
#include <InitTools/InitWindow.h>

namespace InitWindow {

    // FramebufferSize
    void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        auto* self = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
        if(self) {
            self->callback_FramebufferSize(window, width, height);
        }
    }
    void WindowManager::callback_FramebufferSize(GLFWwindow* window, int width, int height) {
        window_size = glm::ivec2(width, height);
        callback_FramebufferSize_custom(width, height);
    }

    // WindowPos
    void window_pos_callback(GLFWwindow* window, int xpos, int ypos) {
        auto* self = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
        if(self) {
            self->callback_WindowPos(window, xpos, ypos);
        }
    }
    void WindowManager::callback_WindowPos(GLFWwindow* window, int xpos, int ypos) {
        window_position = glm::ivec2(xpos, ypos);
        callback_WindowPos_custom(xpos, ypos);
    }

    // CursorPos
    void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
        auto* self = static_cast<WindowManager*>(glfwGetWindowUserPointer(window));
        if(self) {
            self->callback_CursorPos(window, xpos, ypos);
        }
    }
    void WindowManager::callback_CursorPos(GLFWwindow* window, double xpos, double ypos) {
        mouse_position = glm::ivec2(xpos, ypos);
        callback_CursorPos_custom(xpos, ypos);
    }
};
