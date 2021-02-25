#version 330 core

in  vec3 v_fragColor;
out vec4 color;

void main() {
    color = vec4(v_fragColor, 1.0f);
}
