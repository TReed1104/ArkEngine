#version 330
// Generic In variables for a fragment shader
in vec3 fragmentPosition;
in vec3 fragmentColour;
in vec2 fragmentUV;
in vec3 fragmentNormal;

// Generic Out variables for a fragment shader
out vec4 outputColour;

// Universal uniforms, these match shadertoys
uniform vec3 iResolution;
uniform float iTime;
uniform vec4 iMouse;
uniform vec3 iCameraPosition;

// Light Struct, encapsulates the light attributes
struct Light {
    // General lighting attributes
    vec3 position; 
    vec3 direction;

    // Colours and intensities
    vec3 ambientIntensity;
    vec3 diffuseColour;
    vec3 specularIntensity;

    // Spotlighting
    float spotlightCutOff;
    float spotlightCutOffOuter;
    
    // Attenuation
    float attenuationConstant;
    float attenuationLinear;
    float attenuationQuadratic;
};

uniform Light light;

void main() {
    // Ambient
    vec3 ambient = light.ambientIntensity * fragmentColour;
    
    // Diffuse
    vec3 normal = normalize(fragmentNormal);
    vec3 lightDirection = normalize(light.position - fragmentPosition);
    vec3 diffuse = light.diffuseColour * max(dot(normal, lightDirection), 0.0) * fragmentColour;

    // Specular
    vec3 viewDirection = normalize(iCameraPosition - fragmentPosition);
    vec3 reflectdirection = reflect(-lightDirection, normal);
    float shininess = 32;
    vec3 specular = light.specularIntensity * pow(max(dot(viewDirection, reflectdirection), 0.0f), shininess) * fragmentColour;

    // Spotlighting
    float spotlightTheta = dot(lightDirection, normalize(-light.direction));
    float spotlightEpsilon = (light.spotlightCutOff - light.spotlightCutOffOuter);
    float spotlightIntensity = clamp((spotlightTheta - light.spotlightCutOffOuter) / spotlightEpsilon, 0.0, 1.0);
    diffuse *= spotlightIntensity;
    specular *= spotlightIntensity;

    // Attenuation
    float distanceFromLight = length(light.position - fragmentPosition);
    float attenuation = 1.0 / (light.attenuationConstant + light.attenuationLinear * distanceFromLight + light.attenuationQuadratic * (distanceFromLight * distanceFromLight));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    // Set the output colour
    outputColour = vec4((ambient + diffuse + specular), 1.0);
}