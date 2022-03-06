#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 FragColor;

uniform sampler2D ourTexture;// GLSL 采样器

void main()
{
    FragColor=texture(ourTexture,TexCoord);
    // FragColor=texture(ourTexture,TexCoord)*vec4(ourColor,1.f); // 纹理 & 颜色属性
    // texture 使用纹理坐标 TexCoord 从纹理 outTexture 中采样颜色值
    // 返回过滤后的颜色
}