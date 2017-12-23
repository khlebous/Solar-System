#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;

void main()
{
   vec4 tmp =  proj *(view *(model * vec4(aPos, 1.0)));
	//vec4 tmp =  view *(model * vec4(aPos.x, aPos.y, aPos.z, 1.0));
	//tmp = vec4(tmp.x/tmp.w, tmp.y/tmp.w, tmp.z/tmp.w,1.0 );
	//tmp = vec4((tmp.x+1.0)/2.0, (tmp.y+1.0)/2.0,(tmp.z+1.0)/2.0, 1);
	
	//tmp = vec4((tmp.x+1.0)/2.0, (tmp.y+1.0)/2.0,0.0, 1);
	//tmp = vec4(tmp.x, tmp.y, tmp.z, 1);
	
	//tmp = model * vec4(aPos.x, aPos.y, aPos.z,1.0);
	//tmp = vec4((tmp.x)/2.0, (tmp.y)/2.0,(tmp.z)/2.0, 1);
	
	//tmp = vec4(aPos, 1.0);
	
	gl_Position = tmp;
    ourColor = aColor;
}