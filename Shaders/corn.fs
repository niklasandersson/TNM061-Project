#version 330 core

in vec2 UV;
in vec3 Position_worldspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace[10];
in vec3 Normal_cameraspace;
in vec4 shadowCoord;

out vec4 color;

uniform sampler2D DiffuseTextureSampler;
uniform sampler2D AlphaTextureSampler;
uniform sampler2D NormalTextureSampler;
uniform sampler2D ShadowMapSampler;

uniform int numberOfLights;
uniform vec3 lightColors[12];
uniform float lightIntensities[12];
uniform float lightRadii[12];
uniform int lightTypes[12];
uniform vec3 lightPositions[12];
uniform float Time;

float rand(vec2 co)
{
    return fract(sin(Time* dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{

	float materialAlpha = texture2D( AlphaTextureSampler, UV).r;
	vec3 materialDiffuseColor = texture2D( DiffuseTextureSampler, UV).rgb;
	
	vec3 materialAmbientColor = vec3(0.1, 0.1, 0.1) * materialDiffuseColor;
	vec3 materialSpecularColor = vec3(1.0,1.0,1.0);
	float materialSpecularIntensity = 1;
	float materialSpecularFaktor = 5;
	

	//vec3 n = normalize(texture2D( NormalTextureSampler, vec2(UV.x , -UV.y)).rgb * 2 - 1);
	vec3 n = normalize(Normal_cameraspace);
	vec3 l[12];
	float diffuseAngle[12];
	float specularAngle[12];
	float distance[12];

	vec3 specular;
	vec3 diffuse;

	vec3 E = normalize(EyeDirection_cameraspace);
	vec3 R[12];

	for (int i = 0; i < 12; i++)
	{
		l[i] = normalize(LightDirection_cameraspace[i]);
		R[i] = reflect(-l[i], n);
		diffuseAngle[i] = clamp(dot(n,l[i]),0,1);
		specularAngle[i] = clamp(dot(E, R[i]),0,1);

		distance[i] = length(lightPositions[i] - Position_worldspace);

		specular += lightIntensities[i] * materialSpecularColor *lightColors[i] * pow(specularAngle[i],10) * materialSpecularIntensity / (0.5*distance[i]);
		diffuse += lightIntensities[i] * materialDiffuseColor * lightColors[i] * diffuseAngle[i] / (0.08*distance[i]);
	}

	//float visibility = texture( ShadowMapSampler, vec3(shadowCoord.xy, (shadowCoord.z)/shadowCoord.w) );

	color.xyz = (1) * ( (diffuse + specular));
	color.a = materialAlpha;
	//color.xyz = visibility*vec3(1,1,1);
	//color.xyz = n;
	
}