#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    // TexCoords = aPos;
    // gl_Position = projection * view * vec4(aPos, 1.0);

    /* 优化 提前深度测试(Early Depth Testing) */
    TexCoords = aPos;
    vec4 pos = projection * view * vec4(aPos, 1.0);
    gl_Position = pos.xyww; // 让天空盒的 z 深度，永远以 1 进入后续的深度测试
}