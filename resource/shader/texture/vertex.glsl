#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoor;

uniform mat4 u_ProjViewMat;
uniform mat4 u_ModelMat;

out vec2 v_texCoor;

void main() {
    gl_Position = u_ProjViewMat * u_ModelMat * position;
    v_texCoor = texCoor;
}
