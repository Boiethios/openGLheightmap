#version 330 core

layout(location = 0) in vec3 in_Vertex;

out float out_Z;

void main()
{
	gl_Position = vec4(in_Vertex.x / 10., in_Vertex.y / 10., in_Vertex.z, 1.);
	out_Z = in_Vertex.z;
}
