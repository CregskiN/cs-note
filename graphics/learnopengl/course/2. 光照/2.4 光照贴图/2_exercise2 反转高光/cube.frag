#version 330 core

// 当描述一个物体的时候，我们可以用这三个分量来定义一个材质颜色(Material Color)：
// 环境光照(Ambient Lighting)、漫反射光照(Diffuse Lighting)和镜面光照(Specular Lighting)
// 通过为每个分量指定一个颜色，我们就能够对物体的颜色输出有着精细的控制了

struct Material{
    sampler2D diffuse;// 漫反射光照下，物体反射的颜色，通常也是物体颜色
    sampler2D specular;// 在 specular 下，对 R G B 三色的反射程度 // 即物体颜色
    float shininess;// 镜面高光的散射/半径
};

struct Light{// 光线在物体表面，三种反射的强度
    vec3 position;
    vec3 ambient;// ambient 下，光在物体表面反射的比率
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    // 环境光项 ambient
    vec3 ambient=light.ambient*vec3(texture(material.diffuse,TexCoords).rgb);
    
    // 漫反射项 diffuse
    vec3 normal=normalize(Normal);
    vec3 lightDir=normalize(light.position-FragPos);
    float diff=max(dot(normal,lightDir),0.f);
    vec3 diffuse=light.diffuse*diff*vec3(texture(material.diffuse,TexCoords));
    
    // 高光项 specular
    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 reflectDir=reflect(-lightDir,normal);
    float spec=pow(max(dot(viewDir,reflectDir),0.),material.shininess);
    vec3 specular=light.specular*spec*(vec3(1.)-vec3(texture(material.specular,TexCoords)));
    
    FragColor=vec4(ambient+specular+diffuse,1.f);
}