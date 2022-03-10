#version 330 core

// 当描述一个物体的时候，我们可以用这三个分量来定义一个材质颜色(Material Color)：
// 环境光照(Ambient Lighting)、漫反射光照(Diffuse Lighting)和镜面光照(Specular Lighting)
// 通过为每个分量指定一个颜色，我们就能够对物体的颜色输出有着精细的控制了

struct Material{
    vec3 ambient;// 环境光照下，物体反射颜色（通常与物体颜色相同）
    vec3 diffuse;// 漫反射光照下，物体反射的颜色，通常也是物体颜色
    vec3 specular;// 镜面光照对物体颜色影响
    float shininess;// 镜面高光的散射/半径
};

struct Light{// 光线在物体表面，三种反射的强度
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform Material material;

void main()
{
    // 环境光项 ambient
    vec3 ambient=light.ambient*material.ambient;
    
    // 漫反射项 diffuse
    vec3 normal=normalize(Normal);
    vec3 lightDir=normalize(light.position-FragPos);
    vec3 diffuse=light.diffuse*(max(dot(normal,lightDir),0.f)*material.diffuse);
    
    // 高光项 specular
    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 halfVector=normalize(lightDir+viewDir);
    vec3 specular=light.specular*(pow(max(0.f,dot(halfVector,normal)),material.shininess)*material.specular);
    
    FragColor=vec4(diffuse+ambient+specular,1.f);
}