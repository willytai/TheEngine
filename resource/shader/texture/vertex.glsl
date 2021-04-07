#version 410 core

layout(location = 0) in vec3  position;
layout(location = 1) in vec4  color;
layout(location = 2) in vec2  texCoor;
layout(location = 3) in float samplerID;

uniform mat4 u_ProjViewMat;

out vec2  v_texCoor;
out vec4  v_color;
out float v_samplerID;

void main() {
    gl_Position = u_ProjViewMat * vec4(position, 1.0f);
    v_samplerID = samplerID;
    v_texCoor = texCoor;
    v_color = color;
}
