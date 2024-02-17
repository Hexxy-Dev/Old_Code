#pragma once

#include "../Model/Mesh.h"

#include "../Primitives/Vertex.h"

#include "glm.hpp"

#include <vector>

#include "../Profiler.h"

Mesh* createQuad()
{
    PROFILE_FUNCTION();
    std::vector<Vertex> vertices;

    Vertex vertex;

    vertex.Normal = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
    //  0.5f,  0.5f, 0.0f         // -0.5f, -0.5f, 0.0f
    //- 0.5f, -0.5f, 0.0f         //- 0.5f, -0.5f, 0.0f
    vertex.Position = glm::vec3(-0.5f, -0.5f, 0.0f);
    vertex.Color = glm::vec4(1.0f, 0.0f, 0.0f, 0.5f);
    vertex.TexCoords = glm::vec2(0.0f, 0.0f);
    vertices.push_back(vertex);

    vertex.Position = glm::vec3(0.5f, -0.5f, 0.0f);
    vertex.Color = glm::vec4(0.0f, 1.0f, 0.0f, 0.5f);
    vertex.TexCoords = glm::vec2(1.0f, 0.0f);
    vertices.push_back(vertex);

    vertex.Position = glm::vec3(0.5f, 0.5f, 0.0f);
    vertex.Color = glm::vec4(0.0f, 0.0f, 1.0f, 0.5f);
    vertex.TexCoords = glm::vec2(1.0f, 1.0f);
    vertices.push_back(vertex);

    vertex.Position = glm::vec3(-0.5f, 0.5f, 0.0f);
    vertex.Color = glm::vec4(0.0f, 1.0f, 1.0f, 0.5f);
    vertex.TexCoords = glm::vec2(0.0f, 1.0f);
    vertices.push_back(vertex);

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };

    return new Mesh(vertices, indices, true);
}


Mesh* createTexQuad()
{
    PROFILE_FUNCTION();
    std::vector<Vertex> vertices;

    Vertex vertex;

    vertex.Normal = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
    vertex.Color = glm::vec4(1.0f);
    //  0.5f,  0.5f, 0.0f         // -0.5f, -0.5f, 0.0f
    //- 0.5f, -0.5f, 0.0f         //- 0.5f, -0.5f, 0.0f
    vertex.Position = glm::vec3(-0.5f, -0.5f, 0.0f);
    vertex.TexCoords = glm::vec2(0.0f, 0.0f);
    vertices.push_back(vertex);

    vertex.Position = glm::vec3(0.5f, -0.5f, 0.0f);
    vertex.TexCoords = glm::vec2(1.0f, 0.0f);
    vertices.push_back(vertex);

    vertex.Position = glm::vec3(0.5f, 0.5f, 0.0f);
    vertex.TexCoords = glm::vec2(1.0f, 1.0f);
    vertices.push_back(vertex);

    vertex.Position = glm::vec3(-0.5f, 0.5f, 0.0f);
    vertex.TexCoords = glm::vec2(0.0f, 1.0f);
    vertices.push_back(vertex);

    std::vector<unsigned int> indices = {
        0, 1, 2,
        2, 3, 0
    };

    return new Mesh(vertices, indices);
}