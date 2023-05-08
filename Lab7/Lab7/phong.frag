#version 450 core

layout (location = 0) out vec4 fColour;

in vec3 col;
in vec3 nor;
in vec3 FragPosWorldSpace;

uniform vec3 lightDirection;
uniform vec3 lightColour;
uniform vec3 camPos;

void main()
{
	float ambient = 0.1f;  

	vec3 Nnor = normalize(nor);
	vec3 Nto_light = -normalize(lightDirection);
	
	float diffuse = dot(Nnor, Nto_light);

	vec3 Nfrom_light = normalize(lightDirection);
	vec3 NrefLight = reflect(Nfrom_light, Nnor);
	vec3 camDirection = camPos - FragPosWorldSpace;
	vec3 NcamDirection = normalize(camDirection);
	
	float specular = pow(dot(NcamDirection, NrefLight), 128);

	float phong = ambient + diffuse + specular;

	fColour = vec4(phong * col * lightColour, 1.0f);
}
