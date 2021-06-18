#version 330 core

layout (location=0) in vec4 pos;

out vec4 colour;

void main(){
	gl_Position=pos;
	colour=vec4(0.0, 0.0, 0.0,1.0);
}
