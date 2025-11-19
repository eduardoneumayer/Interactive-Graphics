#pragma once
#include <glad/glad.h>
#include <vector>
#include <string>

class Texture
{
    public:
        Texture(std::vector<std::string> faces);
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
