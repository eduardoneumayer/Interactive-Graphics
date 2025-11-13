#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;


out vec3 objectColor;
out vec3 FragPos;
out vec3 Normal;
out vec3 lightPos;
out vec2 TexCoord;

uniform mat4 camMatrix;
uniform vec3 ulightPos;

uniform mat4 modelView;
uniform mat3 normalMatrix;

void main()
{
    FragPos = vec3( modelView *  vec4(pos, 1.0));
    Normal = normalMatrix * aNormal;
    lightPos = vec3(modelView * vec4(ulightPos, 1.0));
    gl_Position = camMatrix * vec4(pos, 1);
    objectColor = vec3(1.0f,0.0f,0.0f);
    TexCoord = aTexCoord;
}