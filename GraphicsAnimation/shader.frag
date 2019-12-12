#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 outNormal;
layout(location = 3) in vec3 fragLoc;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D texSampler;

void main() {
	vec3 lightLocation = vec3(0.0,3.0,-7.0);
	vec3 normal = normalize(outNormal);
	vec3 lightDirection = normalize(lightLocation - fragLoc);
	float diffuseIntensity = max(dot(normal, lightDirection), 0.0);
	vec3 diffuseLight = diffuseIntensity * vec3(1.0f,1.0f,1.0f);

	float ambientLightIntensity = 0.1f;
	vec3 ambientLight = ambientLightIntensity * vec3(1.0f,1.0f,1.0f);
	
	vec3 lightAdded = (ambientLight + diffuseLight) * fragColor;

	outColor = vec4(lightAdded, 1.0);
	//outColor = vec4(fragColor, 1.0);

	//outColor = texture(texSampler, fragTexCoord);
	//outColor = vec4(fragTexCoord, 0.0, 1.0);
}