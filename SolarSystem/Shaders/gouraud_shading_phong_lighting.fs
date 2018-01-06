#version 330 core
out vec4 FragColor;

in vec3 LightingColor; 
in vec3 ourColor;

void main()
{
   FragColor = vec4(LightingColor * ourColor, 1.0);
}