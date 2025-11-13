#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "graphics/renderer/Shader.hpp"
#include "graphics/renderer/VertexBuffer.hpp"
#include "graphics/renderer/VertexArray.hpp"
#include "graphics/renderer/ElementBuffer.hpp"
#include "graphics/renderer/Load.hpp"
#include "core/Camera.hpp"
#include "graphics/lightning/Light.hpp"
#include "graphics/renderer/Texture.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    // inicializando shaderProgram (seu construtor ja é inicializado junto com tudo que está nele)
    Shader shaderProgram("shaders/shader.vert", "shaders/shader.frag");
    std::vector<float> vertices;
    std::vector<float> uvs;

    // Carregando arquivo obj com a classe load
    Load load;
    load.loadObjFile(vertices, uvs, "resources/teapot.obj", false);
    load.triangleIndex.shrink_to_fit();

    // inicializando e bindando vao
    VAO VAO;
    VAO.Bind();

    // inicializando e linkando vbo em vao
    VBO VBO1(vertices, vertices.size() * sizeof(float));
    VAO.LinkVBO(VBO1, 0, 0, 3);     // layout, multiplicador e dimensão, respectivamente

    // Cria o buffer com as normal que estarao no layout location 0 do vertex shader (VBO)
    VBO VBOnormal(load.normal, load.normal.size() * sizeof(float));
    VAO.LinkVBO(VBOnormal, 1, 3, 3);

    // Criar VBO para coords da textura e linkar para mandar pro shader
    VBO VBOtex(uvs, uvs.size() * sizeof(float));
    VAO.LinkVBO(VBOtex, 2, 6, 2);

    // inicializando EBO 
    EBO EBO( load.triangleIndex.data(),  load.triangleIndex.size() * sizeof(load.triangleIndex.front()) );

    VAO.Unbind();
    VBO1.Unbind();
    VBOnormal.Unbind();
    VBOtex.Unbind();
    EBO.unbindBuffer();

    // inicializando o light program 
    Shader lightProgram("shaders/light.vert", "shaders/light.frag");
    [[maybe_unused]] Light light;
    glm::mat4 ulightPos = glm::mat4(1.0f);
    glm::mat4 camMatrix(1.0f);


    glm::mat4 objPos = glm::mat4(1.0f);
    // objPos = glm::translate(objPos,glm::vec3(0.0, 0.0, -10.0));
    objPos = glm::rotate(objPos, glm::radians(-90.0f),glm::vec3(1.0, 0.0, 0.0));
    objPos = glm::scale(objPos, glm::vec3(0.5, 0.5, 0.5));

    // Inicializando camera
    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, -2.0f, 0.0f));

    // Inicializando Textura
    Texture texture("resources/brick.png");

    shaderProgram.Activate();
    shaderProgram.sendUniform("tex", 0);

    glEnable(GL_DEPTH_TEST);
    // render loop 
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        glm::mat4 model(1.0f);
        glm::mat4 view(1.0f);
        glm::mat4 projection(1.0f);


        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);    
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

        // ativa o shader program 
        shaderProgram.Activate();

        // todo o processo de criar as variaveis e mandar essas informações pro shader
        camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix", view, projection, model);
        camera.processInputs(window);

        auto modelView = view * model;
        shaderProgram.sendUniform("modelView", modelView); 
    
        glm::mat3 normalMatrix = glm::inverse((glm::transpose(glm::mat3(view * model))));
        shaderProgram.sendUniform("normalMatrix", normalMatrix);

        light.lightSource = glm::vec4(light.lightSource, 1.0f);

        shaderProgram.sendUniform("ulightPos", light.lightSource);
        shaderProgram.sendUniform("uLightIntensity", light.intensity);
        shaderProgram.sendUniform("uAmbientStrength", light.ambientIntensity);
        shaderProgram.sendUniform("uSpecularStrength", light.specularStrength);
        // shaderProgram.sendUniform("objPos", objPos);

        glPointSize(1.5f);

        // light program infos

        glm::mat4 camMatrixLight = projection * view * model;

        texture.Bind();
        VAO.Bind();
        glDrawElements(GL_TRIANGLES, load.triangleIndex.size(), GL_UNSIGNED_INT, 0);        // desenhando o teapot
        lightProgram.Activate();
        lightProgram.sendUniform("camMatrix", camMatrixLight);      // mandando pro shader
        lightProgram.sendUniform("model", ulightPos);
        light.draw();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}