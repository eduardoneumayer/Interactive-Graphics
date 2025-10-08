#pragma once
#include <glad/glad.h>
#include <vector>

class EBO
{
    public:
        GLuint ebuffer;
        EBO(int* indices, GLsizeiptr size);
        ~EBO();

        void bindBuffer();
        void unbindBuffer();

        GLuint getEBOid();
};