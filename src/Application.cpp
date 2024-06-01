//
// Created by FrancoisMARTEEL on 25/05/2024.
//

#include <vector>

#include "MyRenderingEngine.h"
#include "Application.h"

namespace MyRenderingEngine {

    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    Application::Application() {

    }

    Application::~Application() {

    }

    void Application::Run() {
        InitWindow();
        InitVulkan();
        MainLoop();
        Cleanup();
    }

    void Application::InitWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Hello 42!", nullptr, nullptr);
    }


    void Application::InitVulkan() {
        CreateInstance();
    }

    void Application::CreateInstance() {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello 42!";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "MyRenderingEngine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        createInfo.enabledLayerCount = 0;

        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }

        std::vector<const char*> requiredExtensions;

        for(uint32_t i = 0; i < glfwExtensionCount; i++) {
            requiredExtensions.emplace_back(glfwExtensions[i]);
        }

        requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

        createInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

        createInfo.enabledExtensionCount = (uint32_t) requiredExtensions.size();
        createInfo.ppEnabledExtensionNames = requiredExtensions.data();

        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }

        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> extensions(extensionCount);

        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

        std::cout << "available extensions:\n";

        for (const auto& extension : extensions) {
            std::cout << '\t' << extension.extensionName << '\n';
        }
    }

    void Application::MainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void Application::Cleanup() {
        vkDestroyInstance(instance, nullptr);

        glfwDestroyWindow(window);

        glfwTerminate();
    }
}

