#pragma once
#include <vector>
#include <glad/glad.h>
#include<fstream>
#include<sstream>
#include<iostream>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>     //glm::mat4 identity = glm::mat4(1.0f);
#include <glm/gtc/type_ptr.hpp>             //glm::value_ptr

#include <vector>
#include <memory>

std::string loadFile(const char* filename);

class Shader
{
    public:
        GLuint ID;
        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();

        void sendUniform(const char * uniformVariable, glm::mat4 &matrix4);
        void sendUniform(const char * uniformVariable, glm::mat3 &matrix3);
        void sendUniform(const char * uniformVariable, float &vData);
        void sendUniform(const char * uniformVariable, glm::vec3 &vec);
        
        void Activate();
        void Delete();
};
