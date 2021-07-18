#version 330 core

layout(location = 0) in vec4 pos;
layout(location = 1) in mat4 transformationMatrix;

out vec4 colour;

void main() {
	gl_Position = transformationMatrix * vec4(pos.x, pos.y, pos.z, 1.0f);
	colour = vec4(0.0, 0.0, 0.0, 1.0);
}
