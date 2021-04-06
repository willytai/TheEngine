#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoor;

uniform mat4 u_ProjViewMat;

out vec2 v_texCoor;
out vec4 v_color;

void main() {
    gl_Position = u_ProjViewMat * vec4(position, 1.0f);
    v_texCoor = texCoor;
    v_color = color;
}
