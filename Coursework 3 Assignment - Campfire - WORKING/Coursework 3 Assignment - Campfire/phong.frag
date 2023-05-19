#version 450 core

layout (location = 0) out vec4 fColour;

in vec3 col;
in vec3 nor;
in vec2 tex;
in vec3 FragPosWorldSpace;
in vec4 FragPosProjectedLightSpace;

uniform sampler2D shadowMap;

uniform vec3 lightDirection;
uniform vec3 lightColour;
uniform vec3 lightPos;
uniform vec3 camPos;
uniform float ambient;
uniform bool isDirectionalLight;
uniform bool isNewParticleColour;
uniform vec3 newParticleColour;

float shadowOnFragment(vec4 FragPosProjectedLightSpace)
{
	vec3 ndc = FragPosProjectedLightSpace.xyz / FragPosProjectedLightSpace.w;
	vec3 ss = (ndc + 1) * 0.5;

	float fragDepth = ss.z;

	float litDepth = texture(shadowMap, ss.xy).r;

	vec3 Nnor = normalize(nor);
	vec3 Ntolight = normalize(-lightDirection);

	float bias = max(0.05 * (1.0 - dot(Nnor, Ntolight)), 0.005);
	
	float shadow = 0.0f;

	shadow = fragDepth > (litDepth + bias) ? 1.0 : 0.0;

	if (fragDepth > 1)
	{
		shadow = 0.0f;
	}

	return shadow;
}

float CalculateDirectionalIllumination()
{
	float ambient = 0.1f;  

	vec3 Nnor = normalize(nor);
	vec3 Nto_light = normalize(-lightDirection);
	
	float diffuse = max(dot(Nnor, Nto_light), 0);

	vec3 Nfrom_light = normalize(lightDirection);
	vec3 NrefLight = reflect(Nfrom_light, Nnor);
	vec3 camDirection = camPos - FragPosWorldSpace;
	vec3 NcamDirection = normalize(camDirection);
	
	float specular = pow(max(dot(NcamDirection, NrefLight), 0), 128);

	float shadow = shadowOnFragment(FragPosProjectedLightSpace);

	float phong = ambient + ((1.0f - shadow) * diffuse + specular);

	return phong;
}

float CalculatePositionIllumination()
{
	vec3 Nnor = normalize(nor);
	vec3 Nto_light = normalize(lightPos - FragPosWorldSpace);
	
	float diffuse = max(dot(Nnor, Nto_light),0);

	vec3 Nfrom_light = -Nto_light;
	vec3 NrefLight = reflect(Nfrom_light, Nnor);
	vec3 camDirection = camPos - FragPosWorldSpace;
	vec3 NcamDirection = normalize(camDirection);
	
	float specular = pow(max(dot(NcamDirection, NrefLight), 0), 128);

	float d = length(Nto_light);
	float attenuation = 1.0f / (1.5f + (0.05f * d) + (0.02f * pow(d, 2)));

	float shadow = shadowOnFragment(FragPosProjectedLightSpace);

	return (ambient + ((1.0f - shadow) * diffuse + specular)) * attenuation;
}

void main()
{
	float phong = 0.0f;

	if(isDirectionalLight)
	{
		phong = CalculateDirectionalIllumination();
	}
	else
	{
		phong = CalculatePositionIllumination();
	}

	if(isNewParticleColour)
	{
		fColour = vec4(phong * newParticleColour * lightColour, 1.0f);
	} 
	else
	{
		fColour = vec4(phong * col * lightColour, 1.0f);
	}
}
