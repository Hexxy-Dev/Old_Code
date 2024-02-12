#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

//opengl is a standard and acts as a state machine


/* provide opengl with the source of the shaders compile them link them and create a full shader */

static unsigned int CompileShader(unsigned int type,const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();  //or &source[0] tough not recommended
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    /* check for errors */
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
            << " shader!" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}


static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    // glDetachShader(vs); free up memory   not advised as it hinders debug-ability
    // should be used only after the program is full

    return program;
}

int main(void) {
    GLFWwindow* window;

    /* Initialize the GLFW library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "My window", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize GLEW */
    if (glewInit() != GLEW_OK)
        std::cout << "Glew Error!" << std::endl;

    /* print opengl version */
    std::cout << glGetString(GL_VERSION) << std::endl;


    /* data of buffer */
    float positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    /* create a variable to store the buffer id*/
    unsigned int buffer;

    /* Generate a buffer */
    glGenBuffers(1, &buffer);

    /* select buffer */
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    /* fill the selected buffer with data */
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW); //GL_DYNAMIC_DRAW

    /* set: 
        the start of the buffer
        the number of elements per vertex 
        the type of data
        should be normalized?
        the number of bytes until the next vertex
        the start of the vertex */
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    /* enabe the vertex by passing the vertex index */
    glEnableVertexAttribArray(0);

    /* shaders are programs that run on the GPU. common shaders: vertex and fragment.
       there also exists other types of shaders like compute shaders
       vertex shader is a program that determines the position of the vertexies
       and passes the data to the fragment shader. The vertex shader gets called
       once per each vertex. 
       fragment shader is also a program that determines the colour of each pixel
       to fill the shape determined by the vertexies. The fragment shader gets called
       once per pixel thus millions of time so it needs to be as optimised as possible*/

    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "\n"
        "void main() {\n"
        "   gl_Position = position;\n"
        "}\n";
    std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;\n"
        "\n"
        "void main() {\n"
        "   color = vec4(1.0, 0.0, 0.0, 0.1);\n"
        "}\n";// color is r g b a
    /* create the shader */
    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    /* use the shader */
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Draw the selected buffer */
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 3, NULL);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}