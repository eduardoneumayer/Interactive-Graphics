#include "Camera.hpp"


Camera::Camera(int width, int height, glm::vec3 positions)
{
    Camera::width = width;
    Camera::height = height;
    cameraPos = positions;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform, glm::mat4 &view,glm::mat4 &projection, glm::mat4 &model)
{

    // cria a matriz de visao da nossa camera
    view = glm::lookAt(cameraPos, cameraPos + cameraOrientation, Up);
    // cria a matriz de projeção da nossa camera
    projection = glm::perspective(glm::radians(FOVdeg), float(width) / float(height), nearPlane, farPlane * 100);
    // envia matriz 4v4 pro shader (camMatrix)
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(model * projection * view));
    
}

void Camera::processInputs(GLFWwindow* window)
{
    // WASD
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += speed * cameraOrientation;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraOrientation, Up)) * speed;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= speed * cameraOrientation;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraOrientation, Up)) * speed;

    //UP AND DOWN
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos += speed * Up;
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraPos += speed * -Up;

    // MOUSE INPUTS (ANGLES)
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        // previne o jump da camera no primeiro clique
        if (firstClick){
            glfwSetCursorPos(window, (width/2), (height/2));
            firstClick = false;
        }
        double mouseX;
        double mouseY;
        // pegando a posicao x e y do mouse naquele momento
        glfwGetCursorPos(window, &mouseX, &mouseY);

        // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
        // and then "transforms" them into degrees
        float rotx = sensitivity * (float)(mouseY - (height/2)) / height;
        float roty = sensitivity * (float)(mouseX - (width/2)) / width;

        // calcula mudança na orientacao
        glm::vec3 newOrientation = glm::rotate(cameraOrientation, glm::radians(-rotx), glm::normalize(glm::cross(cameraOrientation, Up)));

        if(abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
        {
            cameraOrientation = newOrientation;
        }
        cameraOrientation = glm::rotate(cameraOrientation, glm::radians(-roty), Up);

        glfwSetCursorPos(window, (width/2), (height/2));
    } 
    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) 
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}

