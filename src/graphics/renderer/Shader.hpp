#pragma once
#include <vector>
#include <glad/glad.h>


class Shader
{
    public:
        GLuint ID;
        Shader();
        ~Shader();
        
        void Activate();
        void Delete();
};
