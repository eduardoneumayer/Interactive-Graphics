#pragma once
#include <glad/glad.h>
#include "VertexBuffer.hpp"

class VAO
{
    
    public:
        GLuint ID;
        VAO();
        ~VAO();

        void LinkVBO(VBO VBO, GLuint layout, GLuint mult, GLuint dimension);
        void Bind();
        void Unbind();
        void Delete();

};