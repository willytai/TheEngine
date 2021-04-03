#version 410 core

layout(location = 0) in vec3 position;

uniform mat4 u_ProjViewMat;
uniform mat4 u_ModelMat;

void main() {
    gl_Position = u_ProjViewMat * u_ModelMat * vec4(position, 1.0f);
}
