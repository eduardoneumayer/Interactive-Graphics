#include "ElementBuffer.hpp"

EBO::EBO(int* indices, GLsizeiptr size)
{
    glGenBuffers(1, &ebuffer); // generate buffer
    bindBuffer();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

EBO::~EBO()
{
    glDeleteBuffers(1, &ebuffer);
}

void EBO::bindBuffer()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebuffer);
}

void EBO::unbindBuffer()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint EBO::getEBOid()
{
    return ebuffer;
}