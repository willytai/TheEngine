#version 410 core

in  vec3 v_color;
out vec4 color;

void main() {
    color = vec4(v_color, 0.5f);
}
