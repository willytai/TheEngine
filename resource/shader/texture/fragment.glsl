#version 460 core

layout(location = 0) out vec4 color;
layout(location = 1) out int  entityID;

struct vertexOut
{
    vec2 texCoor;
    vec4 color;
};

layout (location = 0) in vertexOut vIn;
layout (location = 3) in flat int v_samplerID;
layout (location = 4) in flat int v_entityID;

layout (binding = 0) uniform sampler2D u_Samplers[32];

void main() {
    switch (v_samplerID) {
        case 0 : color = texture(u_Samplers[0],  vIn.texCoor) * vIn.color; break;
        case 1 : color = texture(u_Samplers[1],  vIn.texCoor) * vIn.color; break;
        case 2 : color = texture(u_Samplers[2],  vIn.texCoor) * vIn.color; break;
        case 3 : color = texture(u_Samplers[3],  vIn.texCoor) * vIn.color; break;
        case 4 : color = texture(u_Samplers[4],  vIn.texCoor) * vIn.color; break;
        case 5 : color = texture(u_Samplers[5],  vIn.texCoor) * vIn.color; break;
        case 6 : color = texture(u_Samplers[6],  vIn.texCoor) * vIn.color; break;
        case 7 : color = texture(u_Samplers[7],  vIn.texCoor) * vIn.color; break;
        case 8 : color = texture(u_Samplers[8],  vIn.texCoor) * vIn.color; break;
        case 9 : color = texture(u_Samplers[9],  vIn.texCoor) * vIn.color; break;
        case 10: color = texture(u_Samplers[10], vIn.texCoor) * vIn.color; break;
        case 11: color = texture(u_Samplers[11], vIn.texCoor) * vIn.color; break;
        case 12: color = texture(u_Samplers[12], vIn.texCoor) * vIn.color; break;
        case 13: color = texture(u_Samplers[13], vIn.texCoor) * vIn.color; break;
        case 14: color = texture(u_Samplers[14], vIn.texCoor) * vIn.color; break;
        case 15: color = texture(u_Samplers[15], vIn.texCoor) * vIn.color; break;
        // case 16: color = texture(u_Samplers[16], v_texCoor) * v_color; break;
        // case 17: color = texture(u_Samplers[17], v_texCoor) * v_color; break;
        // case 18: color = texture(u_Samplers[18], v_texCoor) * v_color; break;
        // case 19: color = texture(u_Samplers[19], v_texCoor) * v_color; break;
        // case 20: color = texture(u_Samplers[20], v_texCoor) * v_color; break;
        // case 21: color = texture(u_Samplers[21], v_texCoor) * v_color; break;
        // case 22: color = texture(u_Samplers[22], v_texCoor) * v_color; break;
        // case 23: color = texture(u_Samplers[23], v_texCoor) * v_color; break;
        // case 24: color = texture(u_Samplers[24], v_texCoor) * v_color; break;
        // case 25: color = texture(u_Samplers[25], v_texCoor) * v_color; break;
        // case 26: color = texture(u_Samplers[26], v_texCoor) * v_color; break;
        // case 27: color = texture(u_Samplers[27], v_texCoor) * v_color; break;
        // case 28: color = texture(u_Samplers[28], v_texCoor) * v_color; break;
        // case 29: color = texture(u_Samplers[29], v_texCoor) * v_color; break;
        // case 30: color = texture(u_Samplers[30], v_texCoor) * v_color; break;
        // case 31: color = texture(u_Samplers[31], v_texCoor) * v_color; break;
    }

    // this is not supported on OS X
    // case 4 : color = texture(u_Samplers[v_samplerID], v_texCoor) * v_color;

    entityID = v_entityID;
}
