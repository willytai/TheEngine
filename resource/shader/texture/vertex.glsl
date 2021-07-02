#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoor;
layout (location = 3) in int  samplerID;
layout (location = 4) in int  entityID;

layout (std140, binding = 0) uniform GlobalMatrix
{
    mat4 ProjViewMat;
} Camera;

struct vertexOut
{
    vec2 texCoor;
    vec4 color;
};

layout (location = 0) out vertexOut vOut;
layout (location = 3) out flat int v_samplerID;
layout (location = 4) out flat int v_entityID;

void main() {
    gl_Position = Camera.ProjViewMat * vec4(position, 1.0f);
    
    vOut.texCoor = texCoor;
    vOut.color = color;

    v_samplerID = samplerID;
    v_entityID = entityID;
}
