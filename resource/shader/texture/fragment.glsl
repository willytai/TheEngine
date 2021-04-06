#version 410 core

uniform vec4 u_Color;

in  vec2 v_texCoor;
in  vec4 v_color;
out vec4 color;

uniform sampler2D u_textureID;

void main() {
    // color = texture(u_textureID, v_texCoor) * u_Color;
    color = v_color;
}
