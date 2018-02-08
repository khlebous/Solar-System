#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;

out vec3 ourColor;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;  

	gl_Position = proj *(view *(model * vec4(aPos, 1.0)));
    ourColor = aColor;
}