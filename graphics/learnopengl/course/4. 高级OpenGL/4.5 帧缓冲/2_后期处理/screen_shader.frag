#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
    // 在自建的 framebuffer 中，把 texColorBuffer 当作附件，所有的渲染结果都存储到这个纹理
    // 故这里可以通过采样 texColorBuffer 就能得到最终渲染效果
    
    /* 反向效果 */
    // FragColor=vec4(vec3(1.f-texture(screenTexture,TexCoords)),1.f);
    
    /* 灰度化 */
    // FragColor=texture(screenTexture,TexCoords);
    // float average=(FragColor.r+FragColor.g+FragColor.b)/3.;
    // FragColor=vec4(average,average,average,1.);
    
    /* 加权灰度化 */
    // FragColor=texture(screenTexture,TexCoords);
    // float average=.2126*FragColor.r+.7152*FragColor.g+.0722*FragColor.b;
    // FragColor=vec4(average,average,average,1.);
    
    /* 锐化 kernel */
    // const float offset=1./300.;
    // vec2 offsets[9]=vec2[](
        //     vec2(-offset,offset),// 左上
        //     vec2(0.f,offset),// 正上
        //     vec2(offset,offset),// 右上
        //     vec2(-offset,0.f),// 左
        //     vec2(0.f,0.f),// 中
        //     vec2(offset,0.f),// 右
        //     vec2(-offset,-offset),// 左下
        //     vec2(0.f,-offset),// 正下
        //     vec2(offset,-offset)// 右下
    // );
    
    // float kernel[9]=float[](
        //     -1,-1,-1,
        //     -1,9,-1,
        //     -1,-1,-1
    // );
    
    // vec3 sampleTex[9];// 从 texture 中采样的 3*3 颜色
    // for(int i=0;i<9;i++)
    // sampleTex[i]=vec3(texture(screenTexture,TexCoords.st+offsets[i]));
    
    // vec3 col=vec3(0.);
    // for(int i=0;i<9;i++)
    // col+=sampleTex[i]*kernel[i];// newFragColor = FragColor * kernel
    
    // FragColor=vec4(col,1.);
    
    /* 模糊 kernel */
    // const float offset=1./300.;
    // vec2 offsets[9]=vec2[](
        //     vec2(-offset,offset),// 左上
        //     vec2(0.f,offset),// 正上
        //     vec2(offset,offset),// 右上
        //     vec2(-offset,0.f),// 左
        //     vec2(0.f,0.f),// 中
        //     vec2(offset,0.f),// 右
        //     vec2(-offset,-offset),// 左下
        //     vec2(0.f,-offset),// 正下
        //     vec2(offset,-offset)// 右下
    // );
    
    // float kernel[9]=float[](
        //     1./16,2./16,1./16,
        //     2./16,4./16,2./16,
        //     1./16,2./16,1./16
    // );
    
    // vec3 sampleTex[9];// 从 texture 中采样的 3*3 颜色
    // for(int i=0;i<9;i++)
    // sampleTex[i]=vec3(texture(screenTexture,TexCoords.st+offsets[i]));
    
    // vec3 col=vec3(0.);
    // for(int i=0;i<9;i++)
    // col+=sampleTex[i]*kernel[i];// newFragColor = FragColor * kernel
    
    // FragColor=vec4(col,1.);
    
    /* 边缘检测 kernel */
    
    const float offset=1./300.;
    vec2 offsets[9]=vec2[](
        vec2(-offset,offset),// 左上
        vec2(0.f,offset),// 正上
        vec2(offset,offset),// 右上
        vec2(-offset,0.f),// 左
        vec2(0.f,0.f),// 中
        vec2(offset,0.f),// 右
        vec2(-offset,-offset),// 左下
        vec2(0.f,-offset),// 正下
        vec2(offset,-offset)// 右下
    );
    
    float kernel[9]=float[](
        1,1,1,
        1,-8,1,
        1,1,1
    );
    
    vec3 sampleTex[9];// 从 texture 中采样的 3*3 颜色
    for(int i=0;i<9;i++)
    sampleTex[i]=vec3(texture(screenTexture,TexCoords.st+offsets[i]));
    
    vec3 col=vec3(0.);
    for(int i=0;i<9;i++)
    col+=sampleTex[i]*kernel[i];// newFragColor = FragColor * kernel
    
    FragColor=vec4(col,1.);
    
}