#version 330 core
layout(location=0) in vec3 aPos;
uniform mat4 camMatrix;
uniform mat4 ulightPos;
void main()
{
    gl_Position = normalize(camMatrix * ulightPos * vec4(aPos,1.0f));
}
