#version 410 core

in  vec3 v_fragColor;
in  vec2 v_texCoor;
out vec4 color;

uniform sampler2D u_textureID;

void main() {
    color = vec4(v_fragColor, 1.0f) * texture(u_textureID, v_texCoor);
}
