#version 330 core
layout(location=0)in vec3 aPos;
layout(location=1)in vec3 aNormal;
layout(location=2)in vec2 aTexCoords;

out VS_OUT{
	vec2 texCoords;
	vec3 Position;
	vec3 Normal;
}vs_out;

out vec2 TexCoords;
out vec3 Position;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position=projection*view*model*vec4(aPos,1.);
	
	vs_out.texCoords=aTexCoords;
	vs_out.Position=vec3(model*vec4(aPos,1.f));
	vs_out.Normal=mat3(transpose(inverse(model)))*aNormal;
	
	TexCoords=aTexCoords;
	Position=vec3(model*vec4(aPos,1.f));
	Normal=aNormal;
}