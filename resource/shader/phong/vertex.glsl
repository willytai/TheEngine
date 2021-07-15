#version 460 core

layout (std140, binding = 0) uniform CameraUniform
{
    mat4 ProjViewMat;
    vec3 ViewPos;
} Camera;



layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec4 color;
layout (location = 3) in int  entityID;

struct VertexOut
{
    vec4 color;
    vec3 fragPos;
};

layout (location = 0) out VertexOut v_out;
layout (location = 4) out flat vec3 v_normal;
layout (location = 6) out flat int v_entityID;

void main() {
    gl_Position = Camera.ProjViewMat * vec4(position, 1.0f);

    v_out.color = color;
    v_out.fragPos = position;
    v_normal = normal;
    v_entityID = entityID;
}
