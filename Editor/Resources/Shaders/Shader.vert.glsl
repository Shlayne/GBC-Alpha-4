#version 450 core

layout(location = 0) in vec2 i_Position;

layout(std140, binding = 0) uniform Camera
{
	mat4 viewProjection;
};

layout(location = 0) out vec2 o_Position;

void main()
{
	o_Position = i_Position;
	gl_Position = viewProjection * vec4(i_Position, 0.0, 1.0);
}
