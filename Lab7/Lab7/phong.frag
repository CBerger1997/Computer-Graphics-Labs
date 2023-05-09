#version 450 core

layout (location = 0) out vec4 fColour;

in vec3 col;
in vec3 nor;
in vec3 FragPosWorldSpace;

uniform vec3 lightDirection;
uniform vec3 lightColour;
uniform vec3 lightPos;
uniform vec3 camPos;

float CalculateDirectionalIllumination()
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

	return ambient + diffuse + specular;
}

float CalculatePositionIllumination()
{
	float ambient = 0.1f;  

	vec3 Nnor = normalize(nor);
	vec3 Nto_light = normalize(lightPos - FragPosWorldSpace);
	
	float diffuse = dot(Nnor, Nto_light);

	vec3 Nfrom_light = -Nto_light;
	vec3 NrefLight = reflect(Nfrom_light, Nnor);
	vec3 camDirection = camPos - FragPosWorldSpace;
	vec3 NcamDirection = normalize(camDirection);
	
	float specular = pow(dot(NcamDirection, NrefLight), 128);

	float d = length(lightPos - FragPosWorldSpace);
	float attenuation = 1 / (1.5f + (0.05f * d) + (0.02f * pow(d, 2)));

	return (ambient + diffuse + specular) * attenuation;
}

float CalculateSpotIllumination() 
{
	float ambient = 0.1f;  

	vec3 Nnor = normalize(nor);
	vec3 Nto_light = normalize(lightPos - FragPosWorldSpace);
	
	float diffuse = dot(Nnor, Nto_light);

	vec3 Nfrom_light = -Nto_light;
	vec3 NrefLight = reflect(Nfrom_light, Nnor);
	vec3 camDirection = camPos - FragPosWorldSpace;
	vec3 NcamDirection = normalize(camDirection);
	
	float specular = pow(dot(NcamDirection, NrefLight), 128);

	float d = length(lightPos - FragPosWorldSpace);
	float attenuation = 1 / (1.5f + (0.05f * d) + (0.02f * pow(d, 2)));

	float phi = cos(radians(15));
	vec3 NSpotDir = normalize(lightDirection);
	float theta = dot(Nfrom_light, NSpotDir);

	if(theta > phi)
	{
		return (ambient + diffuse + specular) * attenuation;
	}
	else
	{
		return ambient * attenuation;
	}
}

void main()
{
	float phong = CalculatePositionIllumination();

	fColour = vec4(phong * col * lightColour, 1.0f);
}
