#version 330 core

in vec3 v_normal;
in vec4 v_fragPos;
out vec4 color;

uniform vec4 lightPos;
uniform vec3 ambient;
uniform vec3 objColor;
uniform vec3 lightColor;

void main() {
    vec4 lightDir = normalize(lightPos - v_fragPos);
    vec3 diffuse = max(dot(v_normal, lightDir.xyz), 0.0f) * lightColor;
    color = vec4((ambient+diffuse)*objColor, 1.0f);
}
