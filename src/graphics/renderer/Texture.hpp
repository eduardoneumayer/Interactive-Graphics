#pragma once
#include <glad/glad.h>
#include <vector>
#include <string>

class Texture
{
    public:
        Texture(const std::string &textureFile);
        ~Texture();
        GLuint ID;

        void Bind();
        void unBind();

        void setParameters();
        void sendImageData();

        std::string textureFilepath ;
        int imageWidth;
        int imageHeight;
        int nrChannels;
        unsigned char *imageData;
};
