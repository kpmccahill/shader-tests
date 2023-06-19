#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vertColor;
out vec3 vertPosition;
uniform float vertOffset;

void main (){
    gl_Position = vec4(aPos.x + vertOffset, aPos.y - vertOffset, aPos.z, 1.0);
    vertPosition = aPos;
    vertColor = aColor;
}