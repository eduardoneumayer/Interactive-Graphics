#include "Camera.hpp"


Camera::Camera(int width, int height, glm::vec3 positions)
{
    Camera::width = width;
    Camera::height = height;
    cameraPos = positions;
}

void Camera::Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    // cria a matriz de visao da nossa camera
    view = glm::lookAt(cameraPos, cameraPos + cameraOrientation, Up);
    // cria a matriz de projeção da nossa camera
    projection = glm::perspective(glm::radians(FOVdeg), (float)(width/height), nearPlane, farPlane);
    // envia matriz 4v4 pro shader (camMatrix)
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));

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
        cameraPos += Up * speed;
    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraPos += -Up*speed;

    // MOUSE INPUTS (ANGLES)
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        if (firstClick){
            glfwSetCursorPos(window, (width/2), (height/2));
            firstClick = false;
        }
        double mouseX;
        double mouseY;
        // pegando a posicao x e y do mouse naquele momento
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotx = sensitivity * (float)(mouseY - (height/2)) / height;
        float roty = sensitivity * (float)(mouseX - (width/2)) / width;

        glm::vec3 newOrientation = glm::rotate(cameraOrientation, glm::radians(-rotx), glm::normalize(glm::cross(cameraOrientation, Up)));

        if(!(glm::angle(newOrientation, Up) <= glm::radians(5.0f) or (glm::angle(newOrientation, -Up) <= glm::radians(5.0f))))
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

