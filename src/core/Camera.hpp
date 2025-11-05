#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include"graphics/renderer/Shader.hpp"


class Camera
{
    public:
        glm::vec3 cameraPos;
        //we want the camera pointing to the origin
        glm::vec3 cameraOrientation = glm::vec3(0.0f,1.0f,0.0f);
        glm::vec3 Up = glm::vec3(0.0f,0.0f,1.0f);

        int width;
        int height;
        float speed = 0.1f;
        float sensitivity = 100.0f;
        bool firstClick = true;


        //inicializing the constructor 
        Camera(int width, int height, glm::vec3 positions);

        //function that passes parameters of view and projections to the shader (capture the lookAt function)
        void Matrix(float FOVdeg, float nearPlane, float farPlane, Shader& shader, const char* uniform, glm::mat4 &view,glm::mat4 &projection,  glm::mat4 &model);

        // get the inputs 
        void processInputs(GLFWwindow* window);

};

