#version 330 core
#extension GL_ARB_separate_shader_objects : enable

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform float offset;

void main()
{
   ourColor = vec3(aPos.x + offset, aPos.y, aPos.z);
   gl_Position = vec4(ourColor, 1.0);
}