#version 330 core

in float in_Z;

out vec3 out_Color;

void main()
{
#if 1
	if (in_Z < .5)
		out_Color = vec3(1., 0., 0.);
	else
		out_Color = vec3(0., 1., 0.);
#else
	out_Color = vec3(0., 0., 1.);
#endif
}
