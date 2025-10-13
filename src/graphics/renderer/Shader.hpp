#pragma once
#include <vector>
#include <glad/glad.h>
#include<fstream>
#include<sstream>
#include<iostream>

std::string loadFile(const char* filename);

class Shader
{
    public:
        GLuint ID;
        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();
        
        void Activate();
        void Delete();
};
