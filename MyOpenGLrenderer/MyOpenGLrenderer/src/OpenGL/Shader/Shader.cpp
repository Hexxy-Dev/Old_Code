#include "Shader.h"

#include <fstream>
#include <sstream>
#include <cstdio>


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    {
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;

        vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);

            std::stringstream vShaderStream, fShaderStream;
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            vShaderFile.close();
            fShaderFile.close();

            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            printf("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n");
        }
    }
    const char* vertexShaderCode = vertexCode.c_str();
    const char* fragmentShaderCode = fragmentCode.c_str();


    GLuint vertex;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShaderCode, NULL);
    glCompileShader(vertex);

    GLuint fragment;
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragment);

    int  success;
    char infoLog[512];

    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED:%s\n", infoLog);
    }

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED:%s\n", infoLog);
    }


    ID = glCreateProgram();

    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        printf("ERROR::SHADER_PROGRAM::LINKING_FAILED:%s\n", infoLog);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    bind();
}

Shader::~Shader()
{
    unbind();
    glDeleteProgram(ID);
}

void Shader::bind() const
{
    glUseProgram(ID);
}

void Shader::unbind() const
{
    glUseProgram(0);
}

GLint Shader::getUniformLocation(const std::string& name) const
{
    if (UniformLocationCache.find(name) != UniformLocationCache.end())
        return UniformLocationCache[name];
    GLint location = glGetUniformLocation(ID, name.c_str());
    UniformLocationCache[name] = location;
    return location;
}

void Shader::setUniform1i(const std::string& name, const int& value) const
{
    glUniform1i(getUniformLocation(name), value);
}
void Shader::setUniform2i(const std::string& name, const int& value, const int& value1) const
{
    glUniform2i(getUniformLocation(name), value, value1);
}
void Shader::setUniform3i(const std::string& name, const int& value, const int& value1, const int& value2) const
{
    glUniform3i(getUniformLocation(name), value, value1, value2);
}
void Shader::setUniform4i(const std::string& name, const int& value, const int& value1, const int& value2, const int& value3) const
{
    glUniform4i(getUniformLocation(name), value, value1, value2, value3);
}

void Shader::setUniform1f(const std::string& name, const float& value) const
{
    glUniform1f(getUniformLocation(name), value);
}
void Shader::setUniform2f(const std::string& name, const float& value, const float& value1) const
{
    glUniform2f(getUniformLocation(name), value, value1);
}
void Shader::setUniform3f(const std::string& name, const float& value, const float& value1, const float& value2) const
{
    glUniform3f(getUniformLocation(name), value, value1, value2);
}
void Shader::setUniform4f(const std::string& name, const float& value, const float& value1, const float& value2, const float& value3) const
{
    glUniform4f(getUniformLocation(name), value, value1, value2, value3);
}

void Shader::setUniform1f(const std::string& name, const glm::vec1& value) const
{
    glUniform1f(getUniformLocation(name), value.x);
}
void Shader::setUniform2f(const std::string& name, const glm::vec2& value) const
{
    glUniform2f(getUniformLocation(name), value.x, value.y);
}
void Shader::setUniform3f(const std::string& name, const glm::vec3& value) const
{
    glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
}
void Shader::setUniform4f(const std::string& name, const glm::vec4& value) const
{
    glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
}

void Shader::setMat4(const std::string& name, const glm::mat4& value) const
{
    glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}