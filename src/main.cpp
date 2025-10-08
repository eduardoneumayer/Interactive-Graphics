#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include "graphics/renderer/Shader.hpp"
#include "graphics/renderer/VertexBuffer.hpp"
#include "graphics/renderer/VertexArray.hpp"
#include "core/Camera.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;


std::optional<std::vector<float>> loadObjFile(const char * objFilePath)
{
    std::vector<float> vertices;

    std::ifstream file;     //ifstream para leitura de arquivos
    file.open(objFilePath);

    if (!file.good())
    {
        std::cout << "FALHA AO ABRIR ARQUIVO OBJ" << std::endl;
        return std::nullopt;
    }
    else
    {
        std::cout << "Abriu arquivo obj" << std::endl;
    }

    std::string line;
    while (std::getline(file, line))
    { 
        std::string text;
        file >> text;

        if (text == "v")
        {
            float value;
            file >> value;
            vertices.emplace_back(value); // append da primeira coordenada do vertice

            file >> value;
            vertices.emplace_back(value); // segunda coordenada

            file >> value;
            vertices.emplace_back(value); // terceira coordenada
        }
        
    }

    return vertices;
    
}


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
    Shader shaderProgram1("shaders/shader.vert", "shaders/shader.frag");
    std::vector<float> vertices;

    auto loadobjectfile = loadObjFile("resources/teapot.obj");

    if (!loadobjectfile)
    {
        std::cout << "Failed to load OBJ file." << std::endl;
    }
    else
    {
        vertices = loadobjectfile.value();
    }
    vertices.shrink_to_fit();

    // inicializando e bindando vao
    VAO VAO;
    VAO.Bind();

    std::cout << "Vertices.size(): " << vertices.size() << '\n';
    // inicializando e linkando vbo em vao
    VBO VBO1(vertices, vertices.size() * sizeof(float));
    VAO.LinkVBO(VBO1, 0);

    VAO.Unbind();
    VBO1.Unbind();

    // Inicializando camera
    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    glPointSize(1.5f);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // ativa o shader program e desenha com o vao
        shaderProgram1.Activate();

        camera.Matrix(60.0f, 0.1f, 100.0f, shaderProgram1, "camMatrix");
        camera.processInputs(window);

        VAO.Bind();
        glDrawArrays(GL_TRIANGLES, 0, vertices.size()*sizeof(float));

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