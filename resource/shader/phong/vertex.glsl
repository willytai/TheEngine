#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec4 color;
layout (location = 3) in int  entityID;

layout (std140, binding = 0) uniform GlobalUniform
{
    mat4 ProjViewMat;
    vec3 CameraPos;
} Camera;

struct VertexOut
{
    vec4 color;
    vec4 fragPos;
};

layout (location = 0) out VertexOut v_out;
layout (location = 4) out flat vec3 v_normal;
layout (location = 6) out flat int v_entityID;

void main() {
    v_out.color = color;
    v_out.fragPos = Camera.ProjViewMat * vec4(position, 1.0f);
    v_normal = normal;
    v_entityID = entityID;

    gl_Position = v_out.fragPos;
}
