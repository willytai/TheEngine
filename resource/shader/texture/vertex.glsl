#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoor;

uniform mat4 u_ProjViewMat;
uniform mat4 u_Transform;

out vec2 v_texCoor;

void main() {
    gl_Position = u_ProjViewMat * u_Transform * vec4(position, 1.0f);
    v_texCoor = texCoor;
}
