#include "VertexBuffer.hpp"
#include <iostream>

VBO::VBO(std::vector<float> vertices, GLsizeiptr size)
{
    std::cout << "VBO Constructor called " << '\n';
    
    glGenBuffers(1, &ID);   // gerando o nosso vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, ID);  // bindando o nosso VBO criado no target GLARRAYBUFFER
    // copiando os dados dos vertices a serem espelhados para o buffer criado anteriormente
    glBufferData(GL_ARRAY_BUFFER, size, vertices.data(), GL_STATIC_DRAW);

}

VBO::~VBO()
{
        std::cout << "VBO Destructor called " << '\n';
}

void VBO::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);  // bindando o nosso VBO criado no target GLARRAYBUFFER
}

void VBO::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);  // bindando o nosso VBO criado no target GLARRAYBUFFER
}

void VBO::Delete()
{
    glDeleteBuffers(1, &ID);
}