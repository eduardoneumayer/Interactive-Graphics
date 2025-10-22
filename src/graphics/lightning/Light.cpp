#include "Light.hpp"
#include <iostream>


Light::Light()
{
    std::cout << "Light constructor called" << std::endl;

    createCubeLight();
    createCubeIndices();

    // mesmo esquema de sempre, inicializa o vao, para os vertices para o vbo e indices para ebo, depois da o unbind
    vao = std::make_shared<VAO>();      // make shared evita vazamento de memoria
    vao->Bind();

    vbo = std::make_shared<VBO>(cubeVertices, cubeVertices.size() * sizeof(float));
    vbo->Bind();
    vao->LinkVBO(*vbo, 0);

    ebo = std::make_shared<EBO>(cubeIndices.data(), cubeIndices.size() * sizeof(cubeIndices.front()));      // esse sizeof pega o tamanho do primeiro elemento no vetor cubeIndices

    std::cout << " Num de vertices do cubo = " << cubeVertices.size() / 3 << std::endl;

    vao->Unbind();
    vbo->Unbind();
    ebo->unbindBuffer();

}

Light::~Light()
{
    std::cout << "Light destructor called" << '\n';
}

void Light::draw() const
{
    vao->Bind();
    glDrawElements(GL_TRIANGLES, cubeIndices.size(), GL_UNSIGNED_INT, 0);
    vao->Unbind();
}

void Light::createCubeLight()
{
    float halfsizecube = cubeSize / 2.0f;

    glm::vec3 centercube = lightSource;

    cubeVertices.clear();

    // definir a posicao dos 8 vertices do cubo de luz
    std::vector<glm::vec3> positions = {
        centercube + glm::vec3(-halfsizecube, -halfsizecube, -halfsizecube),
        centercube + glm::vec3( halfsizecube, -halfsizecube, -halfsizecube),
        centercube + glm::vec3( halfsizecube,  halfsizecube, -halfsizecube),
        centercube + glm::vec3(-halfsizecube,  halfsizecube, -halfsizecube),
        centercube + glm::vec3(-halfsizecube, -halfsizecube,  halfsizecube),
        centercube + glm::vec3( halfsizecube, -halfsizecube,  halfsizecube),
        centercube + glm::vec3( halfsizecube,  halfsizecube,  halfsizecube),
        centercube + glm::vec3(-halfsizecube,  halfsizecube,  halfsizecube)
    };
    
    // Insere cada vértice como float (x, y, z)
    for (const auto& pos : positions)
    {
        cubeVertices.push_back(pos.x);
        cubeVertices.push_back(pos.y);
        cubeVertices.push_back(pos.z);
    }

}

void Light::createCubeIndices()
{
    cubeIndices.clear();

    // cada linha de push back define um triangulo, dois triangulos formam uma face
    // Face traseira (z-)
    cubeIndices.push_back(0); cubeIndices.push_back(1); cubeIndices.push_back(2);
    cubeIndices.push_back(2); cubeIndices.push_back(3); cubeIndices.push_back(0);

    // Face dianteira (z+)
    cubeIndices.push_back(4); cubeIndices.push_back(5); cubeIndices.push_back(6);
    cubeIndices.push_back(6); cubeIndices.push_back(7); cubeIndices.push_back(4);

    // Face esquerda (x-)
    cubeIndices.push_back(0); cubeIndices.push_back(3); cubeIndices.push_back(7);
    cubeIndices.push_back(7); cubeIndices.push_back(4); cubeIndices.push_back(0);

    // Face direita (x+)
    cubeIndices.push_back(1); cubeIndices.push_back(5); cubeIndices.push_back(6);
    cubeIndices.push_back(6); cubeIndices.push_back(2); cubeIndices.push_back(1);

    // Face inferior (y-)
    cubeIndices.push_back(0); cubeIndices.push_back(1); cubeIndices.push_back(5);
    cubeIndices.push_back(5); cubeIndices.push_back(4); cubeIndices.push_back(0);

    // Face superior (y+)
    cubeIndices.push_back(3); cubeIndices.push_back(2); cubeIndices.push_back(6);
    cubeIndices.push_back(6); cubeIndices.push_back(7); cubeIndices.push_back(3);

}