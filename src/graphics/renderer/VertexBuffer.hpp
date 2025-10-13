#pragma once
#include <glad/glad.h>
#include <vector>

class VBO
{
    public:
        GLuint ID;
        VBO(std::vector<float> vertices, GLsizeiptr size);

        ~VBO();
        void Bind();
        void Unbind();
        void Delete();

};