#version 410 core

in  vec2 v_texCoor;
out vec4 color;

uniform sampler2D u_textureID;

void main() {
    color = texture(u_textureID, v_texCoor);
}
