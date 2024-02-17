#version 330 core

//layout(location = 0) out vec3 color;
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
in vec4 objectColor;

uniform vec3 CameraPos;

uniform sampler2D colorTexture;
uniform sampler2D specularMap;

float inheritedColorFactor = 0.5f;

struct Light {
    vec3 lightPos;
    vec3 lightColor;

    float ambient;
    float specularLight;
    int specPow;
};

struct PointLight {
    Light light;

    float quadratic;
    float linear;
};
vec3 pointLightFunc(vec3 baseColor, vec3 normal, vec3 viewDir, PointLight pointLight)
{
    vec3 lightVec = pointLight.light.lightPos - FragPos;
    float dist = length(lightVec);
    float intensity = 1.0f / (pointLight.quadratic * dist * dist + pointLight.linear * dist + 1.0f);

    vec3 lightDir = normalize(lightVec);
    float diffuse = max(dot(normal, lightDir), 0.0f);

    vec3 reflectionDir = reflect(-lightDir, normal);
    float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), pointLight.light.specPow);
    float specular = specAmount * pointLight.light.specularLight;

    return ((baseColor + pointLight.light.lightColor * inheritedColorFactor) * (diffuse * intensity) + texture(specularMap, TexCoord).r * specular * intensity) * pointLight.light.lightColor;
}

struct DirectionalLight {
    Light light;

    vec3 direcLightDir;
};
vec3 direcLightFunc(vec3 baseColor, vec3 normal, vec3 viewDir, DirectionalLight direclight)
{
    vec3 lightDir = normalize(direclight.direcLightDir);
    float diffuse = max(dot(normal, lightDir), 0.0f);

    vec3 reflectionDir = reflect(-lightDir, normal);
    float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), direclight.light.specPow);
    float specular = specAmount * direclight.light.specularLight;

    return ((baseColor + direclight.light.lightColor * inheritedColorFactor) * (diffuse) + texture(specularMap, TexCoord).r * specular) * direclight.light.lightColor;
}

struct SpotLight {
    Light light;

    float outerCone;
    float innerCone;
    vec3 spotLightDir;
};
vec3 spotLightFunc(vec3 baseColor, vec3 normal, vec3 viewDir, SpotLight spotlight)
{
    vec3 lightDir = normalize(spotlight.light.lightPos - FragPos);
    float diffuse = max(dot(normal, lightDir), 0.0f);

    vec3 reflectionDir = reflect(-lightDir, normal);
    float specAmount = pow(max(dot(viewDir, reflectionDir), 0.0f), spotlight.light.specPow);
    float specular = specAmount * spotlight.light.specularLight;

    float angle = dot(spotlight.spotLightDir, -lightDir);
    float inten = clamp((angle - spotlight.outerCone) / (spotlight.innerCone - spotlight.outerCone), 0.0f, 1.0f);

    return ((baseColor + spotlight.light.lightColor * inheritedColorFactor) * (diffuse * inten) + texture(specularMap, TexCoord).r * specular * inten) * spotlight.light.lightColor;
}


#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];

#define NR_DIRECTIONAL_LIGHTS 4
uniform DirectionalLight directionalLights[NR_DIRECTIONAL_LIGHTS];

#define NR_SPOT_LIGHTS 4
uniform SpotLight spotLights[NR_SPOT_LIGHTS];

uniform Light ambientLight;

void main()
{
    vec3 baseColor = texture(colorTexture, TexCoord).rgb * objectColor.rgb;

    vec3 normal = normalize(Normal);

    vec3 viewDir = normalize(CameraPos - FragPos);

    vec3 finalColor = vec3(0.0f);

    for(int i = 0; i < NR_DIRECTIONAL_LIGHTS; i++)
    if(directionalLights[i].light.lightColor != vec3(0.0f))
        finalColor += direcLightFunc(baseColor, normal, viewDir, directionalLights[i]);

    for(int i = 0; i < NR_SPOT_LIGHTS; i++)
    if(spotLights[i].light.lightColor != vec3(0.0f))
        finalColor += spotLightFunc(baseColor, normal, viewDir, spotLights[i]);

    for(int i = 0; i < NR_POINT_LIGHTS; i++)
    if(pointLights[i].light.lightColor != vec3(0.0f))
        finalColor += pointLightFunc(baseColor, normal, viewDir, pointLights[i]);

    if(ambientLight.lightColor != vec3(0.0f))
    finalColor += baseColor * ambientLight.ambient * ambientLight.lightColor;

    //color = finalColor;
    FragColor = vec4(finalColor, objectColor.a);
}

// overlapping lights is not handeled right thus artifacts can apprear