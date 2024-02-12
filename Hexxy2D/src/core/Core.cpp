#include "Settings.h"

#include "Core.h"

GLFWwindow* window;

int Core::GL::windowInit(uint16_t sizeY, uint16_t sizeX, const char* name)
{
    if (!glfwInit())
    {
        std::cout << "glfw init failed!\n";
        return -1;
    }
#if DoubleBuffered == 0
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_FALSE);
#endif
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
#if DoubleBuffered == 1
#if VSync == 1
    glfwSwapInterval(1);
#endif
#if VSync == 0
    glfwSwapInterval(0);
#endif
#endif
    if (glewInit() != GLEW_OK)
        std::cout << "Glew Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;

    return 0;
}

void Core::GL::windowRender(gameScene::Scene* currentScene, const Hexxy::Data::array2Dbase<uint8_t>& arrayData, const Hexxy::Data::ColorPaletteBase& colorPalette)
{
    Renderer renderer;

    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        renderer.Clear();

        currentScene->OnUpdate();
        currentScene->OnRender(arrayData, colorPalette);

#if DoubleBuffered == 0
        glFlush();
#else
        glfwSwapBuffers(window);
#endif

        glfwPollEvents();
    } 
}

void Core::GL::CloseWindow()
{
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}