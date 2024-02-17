#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm.hpp"

#include <iostream>

// key callback with key scancode action and mods
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // close the window if the escape key is pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// resize function callback with width and height
void resize_callback(GLFWwindow* window, int width, int height)
{
    // change the viewport if the window is resized
    glViewport(0, 0, width, height);
}

int main()
{
    // window object
    GLFWwindow* window;

    // glfw init
    if (!glfwInit())
        return -1;

    // create a window with 640 by 480 rez and the name "Hello Opengl" in windowed mode
    window = glfwCreateWindow(640, 480, "Hello OpenGL", NULL, NULL);
    if (!window) // if window is not initialized terminate the program
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window); // set the currentlly used window

    glfwWindowHint(GL_VERSION, 3.3); // set the opengl version

    glfwSwapInterval(0);

    glewInit(); // initialize glew


    // create vertices with 3 floats for position and 4 floats for each RGBA channel
    ///*
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,
         0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f
    };//*/

    //create vertex array buffer (Layout buffer)
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO); // bind the buffer

    // create vertex buffer
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // set the data in the buffer to the data in the vertices array
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // set the layout for the buffer
    // first 3 floats are not normalized and at position 0 with a stride of 7 floats and offset 0 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); // enable the layout
    // 4 floats not normalized at position 1 with the same stride and a offset of 3 floats!!!
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // lazy ass way of doing the shader code
    // should* be read from a file
    const char* vertexShaderSource = 
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec4 aColor;\n"
        "out vec4 Color;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "   Color = aColor;\n"
        "}\0";

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);// create vertrx shader

    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);// set the source
    glCompileShader(vertexShader);// compile the shader

    // check if compilation was successfull
    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);//get compilation status
    if (!success)
    {
        // get info
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    const char* fragmentShaderSource =
        "#version 330 core\n"
        "in vec4 Color;\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = Color;\n"
        "}\0";

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);


    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    unsigned int shaderProgram;// create the render program
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader); // bind the shaders
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram); // link the program

    glUseProgram(shaderProgram); // use the program

    glDeleteShader(vertexShader); // delete the shaders
    glDeleteShader(fragmentShader);

    // index buffer
    unsigned int indices[] =
    {
        0, 1, 2
    };

    // create index buffer
    GLuint IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);//bind buffer and set data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    
    // callback for keys
    glfwSetKeyCallback(window, key_callback);

    // callback for resize
    glfwSetFramebufferSizeCallback(window, resize_callback);

    // main render loop
    while (!glfwWindowShouldClose(window))
    {
        // clear color aka background color
        glClearColor(0xff, 0xff, 0xff, 0xff);

        // clear the bit so the color is applied
        glClear(GL_COLOR_BUFFER_BIT);

        // draw the first 3 elements from the IBO and reperesent them as a triangle
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        // swap the buffers for next render
        glfwSwapBuffers(window);

        // poll the events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}