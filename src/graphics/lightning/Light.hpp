#pragma once 
#include<vector>
#include <glad/glad.h>
#include<fstream>
#include<sstream>
#include<iostream>
#include <memory>
#include <glm/glm.hpp>


#include "graphics/renderer/VertexBuffer.hpp"
#include "graphics/renderer/VertexArray.hpp"
#include "graphics/renderer/ElementBuffer.hpp"


class Light
{
    public:
        Light();
        ~Light();

        void draw() const;

        void createCubeLight();
        void createCubeIndices(); 

        glm::vec3 lightSource = glm::vec3(0.0f, 20.0f, 3.0f);       // aonde o cubo de luz vai se localizar

        float cubeSize = 1.0f;
        std::vector<float> cubeVertices;
        std::vector<int> cubeIndices;

        float intensity = 0.5;
        float ambientIntensity = 0.1;       // controlar a luz do que nao ta sendo afetado diretamente
        float specularStrength = 0.9;

        std::shared_ptr<VBO> vbo;
        std::shared_ptr<VAO> vao;
        std::shared_ptr<EBO> ebo;

};