#version 450 core

layout(location = 0) in vec2 i_Position;

layout(location = 0) out vec4 o_Color;

void main()
{
	o_Color = vec4(i_Position / 2.0 + 0.5, 0.0, 1.0);
}
