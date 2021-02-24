#version 330 core

out vec4 color;
in  vec2 v_texCoor;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main() {
    vec4 texColor = texture( u_texture, v_texCoor );
    color = texColor * u_color;
}
