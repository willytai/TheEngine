#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 fragColor;

out vec3 v_fragColor;

void main() {
    gl_Position = position;
    v_fragColor = fragColor;
}
