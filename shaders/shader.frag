#version 330 core
layout(location=0) out vec4 color;

in vec3 objectColor;
in vec3 Normal;
in vec3 FragPos;
in vec3 lightPos;

in vec3 WorldPos;      // do vertex shader
in vec3 WorldNormal;   // do vertex shader

uniform float uLightIntensity;
uniform float uAmbientStrength;
uniform float uSpecularStrength;

// --- NOVOS UNIFORMS ---
uniform samplerCube skybox;
uniform vec3 cameraPos;
uniform float reflectivity;   // 0 = só Phong, 1 = só reflexão


void main()
{
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

    // --- Phong já existente ---
    vec3 ambient = uAmbientStrength * lightColor;
    vec3 norm    = normalize(Normal);
    vec3 lightDir= normalize(lightPos - FragPos);
    float diff   = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    // Specular (Blinn-Phong)
    vec3 E = normalize(-FragPos);
    vec3 L = normalize(lightDir);
    vec3 H = normalize(L + E);
    float spec = pow(max(dot(norm, H), 0.0), 64.0);
    vec3 specular = uSpecularStrength * spec * lightColor;

    vec3 baseColor = uLightIntensity * ((ambient + diffuse + specular) * objectColor);

    // --- REFLEXÃO COM CUBEMAP ---
    // direção da câmera para o fragmento em espaço de mundo
    vec3 I = normalize(WorldPos - cameraPos);
    vec3 Nw = normalize(WorldNormal);
    vec3 R = reflect(I, Nw);

    vec3 envColor = texture(skybox, R).rgb;

    // mistura entre a cor Phong e a reflexão
    vec3 finalColor = mix(baseColor, envColor, reflectivity);

    color = vec4(finalColor, 1.0f);
}
