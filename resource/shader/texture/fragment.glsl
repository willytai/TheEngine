#version 410 core

uniform vec4 u_Color;

in  vec2 v_texCoor;
out vec4 color;

uniform sampler2D u_textureID;

void main() {
    color = texture(u_textureID, v_texCoor) * u_Color;
}
