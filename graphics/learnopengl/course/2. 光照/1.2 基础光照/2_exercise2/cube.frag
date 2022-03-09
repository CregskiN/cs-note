#version 330 core
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 viewPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{    
    // 环境光项 ambient
    float ambientStrength=.2f;
    vec3 ambient=ambientStrength*lightColor;
    
    // 漫反射项 diffuse
    vec3 normal=normalize(Normal);
    vec3 lightDir=normalize(lightPos-FragPos);
    vec3 diffuse=lightColor*max(dot(normal,lightDir),0.f);// 漫反射项
    
    // 高光项 specular
    float specularStrength=.5f;
    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 halfVector=normalize(lightDir+viewDir);
    vec3 specular=specularStrength*lightColor*pow(max(0.f,dot(halfVector,normal)),64);
    
    FragColor=vec4((diffuse+ambient+specular)*objectColor,1.f);
}