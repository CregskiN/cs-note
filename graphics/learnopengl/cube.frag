#version 330 core
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
    // 环境光项 ambient
    float ambientStrength=.1f;
    vec3 ambient=ambientStrength*lightColor;

    // 漫反射项 diffuse
    vec3 normal=normalize(Normal);
    vec3 lightDir=normalize(lightPos-FragPos);
    vec3 diffuse=lightColor*max(dot(normal,lightDir),0.f);// 漫反射项
    
    // 高光项 speculr
    
    FragColor=vec4((diffuse+ambient)*objectColor,1.f);
}