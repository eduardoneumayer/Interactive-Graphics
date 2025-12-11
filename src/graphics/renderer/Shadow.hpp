#pragma once
#include <glad/glad.h>


class Shadow {
public:

    // variables
    GLuint FBO = 0;
    GLuint depthMap = 0;
    int width;
    int height;

    // shadow constructor and destructor

    Shadow(int width = 2048, int height = 2048);
    ~Shadow();

    // functions
    void bind();
    void unbind(int screenWidth, int screenHeight);
};