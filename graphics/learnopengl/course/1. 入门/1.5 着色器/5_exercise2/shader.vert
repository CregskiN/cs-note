#version 330 core
layout(location=0)in vec3 aPos;
layout(location=1)in vec3 aColor;
uniform vec3 move;
out vec3 ourColor;
void main()
{
   gl_Position=vec4(aPos.x+move.x,aPos.y+move.y,aPos.z+move.z,1);
   ourColor=aColor;
   
}