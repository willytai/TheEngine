#version 460 core

layout (std140, binding = 0) uniform CameraUniform
{
    mat4 ProjViewMat;
    vec3 ViewPos;
} Camera;

layout (std140, binding = 1) uniform DirectionalLightUniform
{
    vec3 Direction;
    vec3 Color;

} DirectionalLight;

layout (std140, binding = 2) uniform SceneUniform
{
    float AmbientStrength; // within [0.0 1.0]

    // should be unique per material in the future
    float SpecularStrength; // within [0.0 1.0]
    int   Shininess; // within [1 inf]
} Scene;



layout (location = 0) out vec4 color;
layout (location = 1) out int  entityID;

struct VertexIn
{
    vec4 color;
    vec3 fragPos;
};

layout (location = 0) in VertexIn v_in;
layout (location = 4) in flat vec3 v_normal;
layout (location = 6) in flat int v_entityID;

void main() {
    vec3 norm = normalize(v_normal);
    vec3 lightDirection = normalize(DirectionalLight.Direction);
    vec3 viewDirection = normalize(Camera.ViewPos - v_in.fragPos);

    vec3 ambient = Scene.AmbientStrength * DirectionalLight.Color;

    vec3 diffuse = max(dot(norm, lightDirection), 0.0f) * DirectionalLight.Color;

    float spec = pow(max(dot(viewDirection, reflect(-lightDirection, norm)), 0.0f), Scene.Shininess);
    vec3 specular = Scene.SpecularStrength * spec * DirectionalLight.Color;

    color = vec4((ambient + diffuse + specular) * v_in.color.xyz, v_in.color.w);
    entityID = v_entityID;
}
