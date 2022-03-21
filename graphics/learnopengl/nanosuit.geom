#version 330 core
layout(triangles)in;
layout(triangle_strip,max_vertices=3)out;

in VS_OUT{
    vec2 texCoords;
    vec3 Position;
    vec3 Normal;
}gs_in[];

out vec2 TexCoords;
out vec3 Position;
out vec3 Normal;

uniform float time;

vec4 explode(vec4 position,vec3 normal);
vec3 GetNormal();
void main(){
    vec3 normal=GetNormal();
    
    gl_Position=explode(gl_in[0].gl_Position,normal);
    TexCoords=gs_in[0].texCoords;
    Position=gs_in[0].Position;
    Normal=gs_in[0].Normal;
    EmitVertex();
    
    gl_Position=explode(gl_in[1].gl_Position,normal);
    TexCoords=gs_in[1].texCoords;
    Position=gs_in[1].Position;
    Normal=gs_in[1].Normal;
    EmitVertex();
    
    gl_Position=explode(gl_in[2].gl_Position,normal);
    TexCoords=gs_in[2].texCoords;
    Position=gs_in[2].Position;
    Normal=gs_in[2].Normal;
    EmitVertex();
    
    EndPrimitive();
    
}

vec3 GetNormal(){
    // 三角形摆放顺序？顺时针逆时针？
    vec3 a=vec3(gl_in[0].gl_Position)-vec3(gl_in[1].gl_Position);
    vec3 b=vec3(gl_in[2].gl_Position)-vec3(gl_in[1].gl_Position);
    return normalize(cross(a,b));
}

vec4 explode(vec4 position,vec3 normal){
    float magnitude=0.f;
    vec3 direction=normal*((sin(time)+1.)/2.)*magnitude;
    return position+vec4(direction,0.);
}