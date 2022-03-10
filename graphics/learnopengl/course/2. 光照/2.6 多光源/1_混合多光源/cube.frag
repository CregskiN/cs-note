#version 330 core

// 当描述一个物体的时候，我们可以用这三个分量来定义一个材质颜色(Material Color)：
// 环境光照(Ambient Lighting)、漫反射光照(Diffuse Lighting)和镜面光照(Specular Lighting)
// 通过为每个分量指定一个颜色，我们就能够对物体的颜色输出有着精细的控制了

struct Material{
    sampler2D diffuse;// 漫反射贴图
    sampler2D specular;// 镜面光贴图
    float shininess;// 镜面高光的散射/半径
};

struct DirLight{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight{
    vec3 position;
    float constant;// k_c
    float linear;// k_l
    float quadratic;// k_q
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight{
    vec3 position;
    vec3 direction;
    float cutOff;// phi 内圆锥半径切角余弦值
    float outerCutOff;// gamma 外圆锥半径切角余弦值
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

#define NR_POINT_LIGHTS 4

uniform vec3 viewPos;
uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLight[NR_POINT_LIGHTS];// 需要传入四个点光源参数
uniform SpotLight spotLight;

vec3 CalcDirLight(DirLight light,vec3 normal,vec3 viewDir);
vec3 CalcPointLight(PointLight light,vec3 normal,vec3 FragPos,vec3 viewDir);
vec3 CalcSpotLight(SpotLight light,vec3 normal,vec3 FragPos,vec3 viewDir);

void main()
{
    
    vec3 normal=normalize(Normal);
    vec3 viewDir=normalize(viewPos-FragPos);// shading point 2 camera
    
    vec3 result=CalcDirLight(dirLight,normal,viewDir);
    
    for(int i=0;i<NR_POINT_LIGHTS;++i){
        result+=CalcPointLight(pointLight[i],normal,FragPos,viewDir);
    }
    
    result+=CalcSpotLight(spotLight,normal,FragPos,viewDir);
    
    FragColor=vec4(result,1.f);
    
}

// 计算平行光
vec3 CalcDirLight(DirLight light,vec3 normal,vec3 viewDir){
    vec3 lightDir=normalize(-light.direction);
    // 漫反射着色
    float diff=max(dot(normal,lightDir),0.);
    // 镜面光着色
    vec3 reflectDir=reflect(-lightDir,normal);
    float spec=pow(max(dot(viewDir,reflectDir),0.),material.shininess);
    // 合并结果
    vec3 ambient=light.ambient*vec3(texture(material.diffuse,TexCoords));
    vec3 diffuse=light.diffuse*diff*vec3(texture(material.diffuse,TexCoords));
    vec3 specular=light.specular*spec*vec3(texture(material.specular,TexCoords));
    return ambient+diffuse+specular;
    
}

vec3 CalcPointLight(PointLight light,vec3 normal,vec3 fragPos,vec3 viewDir){
    vec3 lightDir=normalize(light.position-fragPos);
    // 漫反射着色
    float diff=max(dot(normal,lightDir),0.);
    // 镜面光着色
    vec3 reflectDir=reflect(-lightDir,normal);
    float spec=pow(max(dot(viewDir,reflectDir),0.),material.shininess);
    // 衰减
    float distance=length(light.position-fragPos);
    float attenuation=1./(light.constant+light.linear*distance+light.quadratic*(distance*distance));
    // 合并结果
    vec3 ambient=light.ambient*vec3(texture(material.diffuse,TexCoords));
    vec3 diffuse=light.diffuse*diff*vec3(texture(material.diffuse,TexCoords));
    vec3 specular=light.specular*spec*vec3(texture(material.specular,TexCoords));
    ambient*=attenuation;
    diffuse*=attenuation;
    specular*=attenuation;
    return(ambient+diffuse+specular);
}

vec3 CalcSpotLight(SpotLight light,vec3 normal,vec3 fragPos,vec3 viewDir){
    vec3 lightDir=normalize(light.position-fragPos);
    // ambient
    vec3 ambient=light.ambient*texture(material.diffuse,TexCoords).rgb;
    // diffuse
    float diff=max(dot(normal,lightDir),0.f);
    vec3 diffuse=light.diffuse*diff*texture(material.diffuse,TexCoords).rgb;
    // specular
    float spec=pow(max(dot(viewDir,reflect(-lightDir,normal)),0.f),material.shininess);
    vec3 specular=light.specular*spec*texture(material.specular,TexCoords).rgb;
    // attenuation 计算衰减
    float distance=length(light.position-fragPos);
    float attenuation=1./(light.constant+light.linear*distance+light.quadratic*(distance*distance));
    ambient*=attenuation;
    diffuse*=attenuation;
    specular*=attenuation;
    // spotlight soft edges 计算手电筒边缘衰减
    float theta=dot(lightDir,normalize(-light.direction));
    float epsilon=light.cutOff-light.outerCutOff;
    float intensity=clamp((theta-light.outerCutOff)/epsilon,0.,1.);
    ambient*=intensity;
    diffuse*=intensity;
    specular*=intensity;
    
    return ambient+diffuse+specular;
}