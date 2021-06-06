#version 410 core

in  vec2  v_texCoor;
in  vec4  v_color;
flat in int v_samplerID;
flat in int v_entityID;
layout(location = 0) out vec4 color;
layout(location = 1) out int  entityID;

uniform sampler2D u_Samplers[32];

void main() {
    switch (v_samplerID) {
        case 0 : color = texture(u_Samplers[0], v_texCoor) * v_color; break;
        case 1 : color = texture(u_Samplers[1], v_texCoor) * v_color; break;
        case 2 : color = texture(u_Samplers[2], v_texCoor) * v_color; break;
        case 3 : color = texture(u_Samplers[3], v_texCoor) * v_color; break;
        case 4 : color = texture(u_Samplers[4], v_texCoor) * v_color; break;
        case 5 : color = texture(u_Samplers[5], v_texCoor) * v_color; break;
        case 6 : color = texture(u_Samplers[6], v_texCoor) * v_color; break;
        case 7 : color = texture(u_Samplers[7], v_texCoor) * v_color; break;
        case 8 : color = texture(u_Samplers[8], v_texCoor) * v_color; break;
        case 9 : color = texture(u_Samplers[9], v_texCoor) * v_color; break;
        case 10: color = texture(u_Samplers[10], v_texCoor) * v_color; break;
        case 11: color = texture(u_Samplers[11], v_texCoor) * v_color; break;
        case 12: color = texture(u_Samplers[12], v_texCoor) * v_color; break;
        case 13: color = texture(u_Samplers[13], v_texCoor) * v_color; break;
        case 14: color = texture(u_Samplers[14], v_texCoor) * v_color; break;
        case 15: color = texture(u_Samplers[15], v_texCoor) * v_color; break;
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

    entityID = 50;
    entityID = v_entityID;
}
