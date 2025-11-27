#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 objectColor;
out vec3 FragPos;
out vec3 Normal;
out vec3 lightPos;

// NOVO: posição e normal em espaço de mundo p/ reflexão
out vec3 WorldPos;
out vec3 WorldNormal;

uniform mat4 camMatrix;
uniform vec3 ulightPos;

uniform mat4 modelView;
uniform mat3 normalMatrix;

void main()
{
    // espaço da câmera (já usado na iluminação)
    FragPos  = vec3(modelView * vec4(pos, 1.0));
    Normal   = normalMatrix * aNormal;
    lightPos = vec3(modelView * vec4(ulightPos, 1.0));

    // como model é identidade, world = pos/aNormal
    WorldPos    = pos;
    WorldNormal = aNormal;

    gl_Position = camMatrix * vec4(pos, 1);
    objectColor = vec3(1.0f, 0.0f, 0.0f);
}
