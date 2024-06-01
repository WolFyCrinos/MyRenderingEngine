#include "MyRenderingEngine.h"
#include "Application.h"

int main() {
    const auto app =new MyRenderingEngine::Application;

    try {
        app->Run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;

        delete app;

        return EXIT_FAILURE;
    }

    delete app;

    return EXIT_SUCCESS;
}
