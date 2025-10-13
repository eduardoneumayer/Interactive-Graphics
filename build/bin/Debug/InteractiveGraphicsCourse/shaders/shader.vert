#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 camMatrix;

void main()
{
   gl_Position = camMatrix * vec4(aPos * 0.05, 1.0);
};