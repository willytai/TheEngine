#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 fragColor;

uniform mat4 u_ProjViewMat;
uniform mat4 u_ModelMat;

out vec3 v_fragColor;

void main() {
    gl_Position = u_ProjViewMat * u_ModelMat * position;
    v_fragColor = fragColor;
}
