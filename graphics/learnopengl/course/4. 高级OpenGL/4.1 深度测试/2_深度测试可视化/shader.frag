#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

float LinearizeDepth(float depth);

float near=.1;
float far=100.;

void main()
{
    // 深度可视化，即将 fragment.z 作为颜色输出
    // FragColor = texture(texture1, TexCoords);
    float depth=LinearizeDepth(gl_FragCoord.z)/far;// 为了演示除以 far，的到 depth 近似[0, 1]
    FragColor=vec4(vec3(depth),1.);
    
}

float LinearizeDepth(float depth){
    float z=depth*2.-1.;// back to NDC
    return(2.*near*far)/(far+near-z*(far-near));
}