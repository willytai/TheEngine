#version 410 core

in  float v_samplerID;
in  vec2  v_texCoor;
in  vec4  v_color;
out vec4  color;

uniform sampler2D u_Samplers[32];

void main() {
    switch (int(v_samplerID)) {
        case 0 : color = texture(u_Samplers[0], v_texCoor) * v_color; break;
        case 1 : color = texture(u_Samplers[1], v_texCoor) * v_color; break;
        case 2 : color = texture(u_Samplers[2], v_texCoor) * v_color; break;
        case 3 : color = texture(u_Samplers[3], v_texCoor) * v_color; break;
        case 4 : color = texture(u_Samplers[4], v_texCoor) * v_color; break;
    }

    // this is not supported on OS X
    // case 4 : color = texture(u_Samplers[int(v_samplerID)], v_texCoor) * v_color;
}
