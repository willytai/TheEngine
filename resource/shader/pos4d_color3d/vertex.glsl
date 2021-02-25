#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 fragColor;

out vec3 v_fragColor;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    gl_Position = u_projection * u_view * u_model * position;
    v_fragColor = fragColor;
}
