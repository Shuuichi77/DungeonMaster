#version 330 core

in vec3 vFragColor;
in vec2 vCoordTexture;

uniform sampler2D uTexture;

out vec4 fFragColor;

void main() {
    fFragColor = texture(uTexture, vCoordTexture);
};