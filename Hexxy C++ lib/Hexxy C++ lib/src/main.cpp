#include <iostream>

#include "Hexxy/Hexxy.h"
//#include "Tests/Tests.hpp"

//#include "ChromeProfiler.h"
//#include <cmath>
//void Benchmark()
//{
//	PROFILE_FUNCTION();
//
//	Hexxy::Math::Matrix::Mat4 mat1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
//	Hexxy::Math::Matrix::Mat4 mat2(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
//	for (size_t i = 0; i < 100000000; i++) {
//		mat1 *= mat2 * (rand() % 4 + 0.1f);
//		mat2 *= rand() % 2 + 0.1f;
//	}
//	mat1.print();
//
//	Hexxy::Math::Vectors::Vec4 vec1(1, 2, 3, 4);
//	Hexxy::Math::Vectors::Vec4 vec2(5, 6, 7, 8);
//	for (size_t i = 0; i < 100000000; i++) {
//		vec1 *= rand() % 4 + 0.8f;
//		vec1 *= vec2.length();
//		vec2 *= rand() % 2 + 0.8f;
//	}
//	vec1.print();
//	vec2.print();
//}
//#include "../external/GLM/glm/glm.hpp"
//#include "../external/GLM/glm/matrix.hpp"
//void Control()
//{
//	PROFILE_FUNCTION();
//
//	glm::mat4 mat1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
//	glm::mat4 mat2(17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32);
//	for (size_t i = 0; i < 100000000; i++) {
//		mat1 *= mat2 * (rand() % 4 + 0.1f);
//		mat2 *= rand() % 2 + 0.1f;
//	}
//	printf("Mat4x4:\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n",
//		mat1[0][0], mat1[0][1], mat1[0][2], mat1[0][3], mat1[1][0], mat1[1][1], mat1[1][2], mat1[1][3], mat1[2][0], mat1[2][1], mat1[2][2], mat1[2][3], mat1[3][0], mat1[3][1], mat1[3][2], mat1[3][3]);
//
//	glm::vec4 vec1(1, 2, 3, 4);
//	glm::vec4 vec2(5, 6, 7, 8);
//	for (size_t i = 0; i < 100000000; i++) {
//		vec1 *= rand() % 4 + 0.8f;
//		vec1 *= vec2.length();
//		vec2 *= rand() % 2 + 0.8f;
//	}
//	printf("Vec4: %f, %f, %f, %f\n", vec1[0], vec1[1], vec1[2], vec1[3]);
//	printf("Vec4: %f, %f, %f, %f\n", vec2[0], vec2[1], vec2[2], vec2[3]);
//
//}

void Triangle();
void Ogl11Test();

int main() {
//    Hexxy::Tests::All_Tests();

    //Instrumentor::Instance().beginSession("Benchmark");
    //Benchmark();
    //Control();
    //Instrumentor::Instance().endSession();

    //Hexxy::Platforms::Windows::OpenGLWindow window(L"HEXXY C++ LIB");
    //
    //while (window.WindowIsActive()) {
    //    window.ProcessMessage();
    //}

    Ogl11Test();

}

void Ogl11Test()
{
    Hexxy::Platforms::Windows::OpenGLWindow window(L"HEXXY C++ LIB");
    Hexxy::Platforms::Windows::OpenGL::init();


    using namespace Hexxy::Platforms::Windows::OpenGL;

    std::cout << glGetString(GL_VERSION);

    while (window.WindowIsActive())
    {
        glBegin(GL_TRIANGLES);
        glColor4f(1, 0, 0, 1); // red
        glVertex2f(-0.8, -0.8);
        glColor4f(0, 1, 0, 1); // green
        glVertex2f(0.8, -0.8);
        glColor4f(0, 0, 1, 1); // blue
        glVertex2f(0, 0.9);
        glEnd();
        window.ProcessMessage();
    }
}



void Triangle()
{
    

    Hexxy::Platforms::Windows::OpenGLWindow window(L"HEXXY C++ LIB");
    Hexxy::Platforms::Windows::OpenGL::init();
    

    using namespace Hexxy::Platforms::Windows::OpenGL;

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,
         0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f
    };

    //create vertex array buffer (Layout buffer)
    unsigned int VAO = 0;
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

    //glfwSetKeyCallback(window, key_callback);
    //glfwSetFramebufferSizeCallback(window, resize_callback);

    //while (!glfwWindowShouldClose(window))
    while (window.WindowIsActive())
    {
        glClearColor(0xff, 0xff, 0xff, 0xff);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        //glfwSwapBuffers(window);
        //glfwPollEvents();
        window.ProcessMessage();
    }
    //glfwTerminate();
}