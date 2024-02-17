#pragma once

#include "glm.hpp"

#include "glad/glad.h"

#include "stb_image.h"

#include <conio.h>
#include <vector>

enum TextureType {
    ColorTexture
};

static std::vector<GLuint> TexturesList;

struct Texture {

	void loadTexture(const char* Path, const TextureType& Type)
	{

        switch (Type)
        {
        case 0:
            name = "colorTexture";
            break;
        }

        stbi_set_flip_vertically_on_load(true);
        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);
        TexturesList.push_back(ID);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load and generate the texture
        int imageWidth, imageHeight, nrChannels;
        unsigned char* data = stbi_load(Path, &imageWidth, &imageHeight, &nrChannels, 0);
        if (!data)
        {
            printf("Failed to load texture");
        }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);

        glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLuint ID;
    const char* name;

    static void Delete()
    {
        for (int i = 0; i < TexturesList.size(); i++)
        {
            glDeleteTextures(1, &TexturesList[i]);
        }
    }
};