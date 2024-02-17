#pragma once

#include "glad/glad.h"

#include <string>
#include <unordered_map>
#include "glm.hpp"

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    ~Shader();

    void bind() const;
    void unbind() const;


    void setUniform1i(const std::string& name, const int& value) const;
    void setUniform2i(const std::string& name, const int& value, const int& value1) const;
    void setUniform3i(const std::string& name, const int& value, const int& value1, const int& value2) const;
    void setUniform4i(const std::string& name, const int& value, const int& value1, const int& value2, const int& value3) const;

    void setUniform1f(const std::string& name, const float& value) const;
    void setUniform2f(const std::string& name, const float& value, const float& value1) const;
    void setUniform3f(const std::string& name, const float& value, const float& value1, const float& value2) const;
    void setUniform4f(const std::string& name, const float& value, const float& value1, const float& value2, const float& value3) const;

    void setUniform1f(const std::string& name, const glm::vec1& value) const;
    void setUniform2f(const std::string& name, const glm::vec2& value) const;
    void setUniform3f(const std::string& name, const glm::vec3& value) const;
    void setUniform4f(const std::string& name, const glm::vec4& value) const;

    void setMat4(const std::string& name, const glm::mat4& value) const;

private:
    GLuint ID;
    mutable std::unordered_map<std::string, GLint> UniformLocationCache;
private:
    GLint getUniformLocation(const std::string& name) const;
};