//
// Created by FrancoisMARTEEL on 25/05/2024.
//

#pragma once

#ifndef APPLICATION_H
#define APPLICATION_H

#endif //APPLICATION_H

#include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "MyRenderingEngine.h"

namespace MyRenderingEngine {
    class Application {
    public:
        Application();
        ~Application();

        void Run();

    private:
        GLFWwindow* window;
        VkInstance instance;

        void InitWindow();
        void InitVulkan();
        void CreateInstance();
        void MainLoop();
        void Cleanup();
    };
}