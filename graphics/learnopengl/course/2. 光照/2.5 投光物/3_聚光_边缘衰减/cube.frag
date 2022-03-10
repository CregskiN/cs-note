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
    
    float k_constant;
    float k_linear;
    float k_quadratic;
    
    vec3 direction;// 手电筒朝向
    float cos_cutOff;// 内圆锥半径切角余弦值
    float cos_outerCutOff;// 外圆锥半径切角余弦值
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
    vec3 ambient=light.ambient*texture(material.diffuse,TexCoords).rgb;
    
    // 漫反射项 diffuse
    vec3 normal=normalize(Normal);
    vec3 lightDir=normalize(light.position-FragPos);// frag 2 light
    float diff=max(dot(normal,lightDir),0.f);
    vec3 diffuse=light.diffuse*diff*texture(material.diffuse,TexCoords).rgb;
    
    // 高光项 specular
    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 halfVector=normalize(lightDir+viewDir);
    float spec=pow(max(dot(normal,halfVector),0.),material.shininess);
    vec3 specular=light.specular*spec*texture(material.specular,TexCoords).rgb;
    
    // 衰减 attenuation
    float distance=length(light.position-FragPos);
    float attenuation=1.f/(light.k_constant+light.k_linear*distance+light.k_quadratic*(distance*distance));
    ambient*=attenuation;
    diffuse*=attenuation;
    specular*=attenuation;
    
    // spotlight (soft edges)
    float cos_theta=dot(lightDir,normalize(-light.direction));
    float cos_epsilon=light.cos_cutOff-light.cos_outerCutOff;
    float intensity=clamp((cos_theta-light.cos_outerCutOff)/cos_epsilon,0.f,1.f);
    diffuse*=intensity;
    specular*=intensity;
    
    FragColor=vec4(ambient+specular+diffuse,1.f);
    
}