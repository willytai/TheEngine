#version 410 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec3 color;

uniform mat4 u_ProjViewMat;
uniform mat4 u_ModelMat;

out vec3 v_color;

void main() {
    gl_Position = u_ProjViewMat * u_ModelMat * vec4(position, 0.0f, 1.0f);
    v_color = color;
}
