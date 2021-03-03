#version 330 core

in vec3 v_normal;
in vec4 v_fragPos;
in vec4 v_viewPos;
out vec4 color;

uniform int u_shininess;
uniform float u_specularStrength;
uniform vec4 u_lightPos;
uniform vec3 u_ambient;
uniform vec3 u_objColor;
uniform vec3 u_lightColor;

void main() {
    vec4 lightDir = normalize(u_lightPos - v_fragPos);
    vec3 diffuse = max(dot(v_normal, lightDir.xyz), 0.0f) * u_lightColor;
    float spec = max(dot(normalize(v_viewPos-v_fragPos).xyz, reflect(-lightDir.xyz, v_normal)), 0.0f);
    vec3 specular = u_specularStrength * u_lightColor * pow(spec, u_shininess);
    color = vec4((u_ambient+diffuse+specular)*u_objColor, 1.0f);
}
