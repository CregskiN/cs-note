#version 330 core
struct Material{
    sampler2D texture_diffuse1;
    sampler2D texture_reflection1;
};

out vec4 FragColor;

in vec2 TexCoord;
in vec3 Position;
in vec3 Normal;

uniform vec3 cameraPos;
uniform Material material;
uniform samplerCube skybox;

void main()
{
    vec3 viewDir=normalize(cameraPos-Position);
    vec3 normal=normalize(Normal);
    
    vec3 R=reflect(-viewDir,normal);
    vec3 reflectMap=vec3(texture(material.texture_reflection1,TexCoord));
    vec3 reflection=vec3(texture(skybox,R).rgb)*reflectMap;
    
    float diff=max(normalize(dot(normal,viewDir)),0.f);
    vec3 diffuse=diff*vec3(texture(material.texture_diffuse1,TexCoord));
    
    FragColor=vec4(diffuse+reflection,1.f);
}