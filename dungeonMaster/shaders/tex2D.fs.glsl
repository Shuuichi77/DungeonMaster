#version 330

in vec2 vTexCoords;

out vec3 fFragColor;

uniform vec3 uColor;
uniform sampler2D uTexture;

void main() {
    //    fFragColor = uColor;
    fFragColor = texture(uTexture, vTexCoords).rgb;
};