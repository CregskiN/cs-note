#version 330 core
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D texture1;// GLSL 采样器 // 值为纹理单元（即纹理的 GL_TEXTURE0 到 15）
uniform sampler2D texture2;

void main()
{
    FragColor=mix(texture(texture1,TexCoord),texture(texture2,vec2(1-TexCoord.x,TexCoord.y)),0.2);
    // texture 使用纹理坐标 TexCoord 从纹理 outTexture 中采样颜色值
    // 返回过滤后的颜色
}