#include "Settings.h"

#include "Core.h"

#include "ChromeProfiler.h"

GLFWwindow* window;

int Core::GL::windowInit(uint16_t sizeY, uint16_t sizeX, const char* name)
{
#if PROFILING == 1
    PROFILE_FUNCTION();
#endif

    if (!glfwInit())
    {
        std::cout << "glfw init failed!\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#if CORE_FULLSCREEN == 1
    window = glfwCreateWindow(sizeX, sizeY, name, glfwGetPrimaryMonitor(), NULL);
#else
    window = glfwCreateWindow(sizeX, sizeY, name, NULL, NULL);
#endif
    if (!window)
    {
        std::cout << "glfw create window failed!\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

#if VSync == 1
    glfwSwapInterval(1);
#else
    glfwSwapInterval(0);
#endif

    if (glewInit() != GLEW_OK)
        std::cout << "Glew Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 0;
}

#if SHOW_FPS == 1
double previousTime = glfwGetTime();
int frameCount = 0;
#endif
void Core::GL::windowRender(float& Y_Offset, float& X_Offset, gameScene::Scene* currentScene, const Hexxy::Data::array2D& arrayData, const Hexxy::Data::ColorPalette& colorPalette)
{
#if PROFILING == 1
    PROFILE_FUNCTION();
#endif

    Renderer renderer;

    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        renderer.Clear();

        currentScene->OnUpdate();
        currentScene->OnRender(Y_Offset, X_Offset, arrayData, colorPalette);

        GLCall(glfwSwapBuffers(window));

        GLCall(glfwPollEvents());

#if SHOW_FPS == 1
        double currentTime = glfwGetTime();
        frameCount++;
        if (currentTime - previousTime >= 1.0)
        {
            std::cout << "FPS: " << frameCount << "\n";

            frameCount = 0;
            previousTime = currentTime;
        }
#endif
    } 
}

void Core::GL::CloseWindow()
{
    GLCall(glfwSetWindowShouldClose(window, GLFW_TRUE));
}