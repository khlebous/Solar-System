#version 330 core
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColor;
layout (location = 1) in vec3 aNormal;

//out vec3 ourColor;
out vec3 Normal;
out vec3 FragPos;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
    vec4 tmp =  proj *(view *(model * vec4(aPos, 1.0)));	
	
	FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;  

	gl_Position = tmp;
   // ourColor = aColor;
}