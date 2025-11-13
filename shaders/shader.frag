#version 330 core
layout(location=0) out vec4 color;

in vec3 objectColor;
in vec3 Normal;
in vec3 FragPos;
in vec3 lightPos;
in vec2 TexCoord;

uniform float uLightIntensity;
uniform float uAmbientStrength;
uniform float uSpecularStrength; 

uniform sampler2D tex;

void main()
{
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

    vec3 ambient = uAmbientStrength * lightColor;
    vec3 norm    = normalize(Normal);
    vec3 lightDir= normalize(lightPos - FragPos);
    float diff   = max(dot(norm, lightDir), 0.0f);
    vec3 diffuse = diff * lightColor;

    // Specular light
    vec3 E = normalize(-FragPos);
    vec3 L = normalize(lightDir);
    vec3 H = normalize(L + E);

    float spec = pow(max(dot(norm, H), 0.0), 64);
    vec3 specular = uSpecularStrength * spec * lightColor;

    // Texture
    vec3 texColor = texture(tex, TexCoord).rgb;

    vec3 result = uLightIntensity * ( (ambient + diffuse + specular) * objectColor );
    color = vec4(result * texColor, 1.0f);
}
