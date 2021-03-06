#version 330 core
layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_color;
layout(location = 2) in vec2 a_tex;

out vec3 color;
out vec2 texCoord;

void main(){
	gl_Position = vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);
	color = a_color;
	texCoord = a_tex;
}