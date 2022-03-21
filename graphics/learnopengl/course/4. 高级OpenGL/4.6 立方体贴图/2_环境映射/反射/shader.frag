#version 330 core
out vec4 FragColor;

in vec3 Position;
in vec3 Normal;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{
    vec3 incidentDir=normalize(Position-cameraPos);
    vec3 reflectDir=reflect(incidentDir,normalize(Normal));
    FragColor=vec4(texture(skybox,reflectDir).rgb,1.);
}