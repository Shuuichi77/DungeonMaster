#version 330 core

layout (location = 0) in vec2 aVertexPosition;
layout (location = 1) in vec2 aVertexCoordTexture;

out vec3 vFragColor;
out vec2 vCoordTexture;

uniform mat3 uModelMatrix;

void main() {
    vCoordTexture = aVertexCoordTexture;
    vec2 transformed = (uModelMatrix * (vec3(aVertexPosition, 1))).xy;

    vFragColor = vec3(1, aVertexCoordTexture);
    gl_Position = vec4(transformed, 0, 1);
};