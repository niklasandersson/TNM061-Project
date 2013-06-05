#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;
layout(location = 2) in vec2 vertexUV;

out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace[10];
out vec2 UV;
out vec4 shadowCoord;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform mat4 DepthBiasMVP;

uniform int numberOfLights;
uniform vec3 lightPositions[10];

void main()
{
	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
	
	Position_worldspace = (M * vec4(vertexPosition_modelspace,1)).xyz;

	vec3 vertexPosition_cameraspace = ( V * M * vec4(vertexPosition_modelspace,1)).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

	vec3 LightPosition_cameraspace[10];
	for (int i = 0; i < 3; i++)
	{
		LightPosition_cameraspace[i] = ( V * vec4(lightPositions[i],1)).xyz;

		LightDirection_cameraspace[i] = LightPosition_cameraspace[i] + EyeDirection_cameraspace;
	}
	
	Normal_cameraspace = ( V * M * vec4(vertexNormal_modelspace,0)).xyz;

	shadowCoord = DepthBiasMVP * vec4(vertexPosition_modelspace,1);

	UV = vertexUV;
}