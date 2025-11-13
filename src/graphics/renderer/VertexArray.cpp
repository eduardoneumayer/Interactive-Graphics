#include "VertexArray.hpp"
#include <iostream>

VAO::VAO()
{
    std::cout << "VAO constructor called " << '\n';
    glGenVertexArrays(1, &ID);
}

VAO::~VAO()
{
        std::cout << "VAO Destructor called " << '\n';
}

void VAO::LinkVBO(VBO VBO, GLuint layout, GLuint mult, GLuint dimension)
{
    VBO.Bind();
    glVertexAttribPointer(layout, dimension , GL_FLOAT, GL_FALSE,  0, (void*)(mult * sizeof(float)));
    glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO::Bind()
{
    glBindVertexArray(ID);
}

void VAO::Unbind()
{
    glBindVertexArray(0);
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}