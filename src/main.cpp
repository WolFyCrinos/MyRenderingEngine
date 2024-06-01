#include <vk_engine.h>

int main(int argc, char* argv[]) {
    /*const auto app = new MyRenderingEngine::Application;

    try {
        app->Run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;

        delete app;

        return EXIT_FAILURE;
    }

    delete app;

    return EXIT_SUCCESS;*/

    VulkanEngine engine;

    engine.init();

    engine.run();

    engine.cleanup();

    return EXIT_SUCCESS;
}
