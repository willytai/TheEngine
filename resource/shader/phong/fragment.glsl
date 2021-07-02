#version 460 core

layout (location = 0) out vec4 color;
layout (location = 1) out int  entityID;

struct VertexIn
{
    vec4 color;
    vec4 fragPos;
};

layout (location = 0) in VertexIn v_in;
layout (location = 4) in flat vec3 v_normal;
layout (location = 6) in flat int v_entityID;

// uniform int u_shininess;
// uniform float u_specularStrength;
// uniform vec4 u_lightPos;
// uniform vec3 u_ambient;
// uniform vec3 u_objColor;
// uniform vec3 u_lightColor;

void main() {
    vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 1.0f));
    vec3 lightColor = vec3(0.8f, 0.8f, 0.8f);
    vec3 diffuse = max(dot(v_normal, lightDirection), 0.0f) * lightColor;
    vec3 ambient = vec3(0.2f, 0.2f, 0.2f);

    // vec4 lightDir = normalize(u_lightPos - v_fragPos);
    // vec3 diffuse = max(dot(v_normal, lightDir.xyz), 0.0f) * u_lightColor;
    // float spec = max(dot(normalize(v_viewPos-v_fragPos).xyz, reflect(-lightDir.xyz, v_normal)), 0.0f);
    // vec3 specular = u_specularStrength * u_lightColor * pow(spec, u_shininess);
    // color = vec4((u_ambient+diffuse+specular)*u_objColor, 1.0f);

    color = vec4((ambient + diffuse) * v_in.color.xyz, v_in.color.w);
    entityID = v_entityID;
}
