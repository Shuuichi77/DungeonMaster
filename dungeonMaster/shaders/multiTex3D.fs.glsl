#version 330

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

uniform sampler2D uEarthTexture;
uniform sampler2D uCloudTexture;

out vec3 fFragColor;

void main() {
    fFragColor = texture(uEarthTexture, vTexCoords).rgb + texture(uCloudTexture, vTexCoords).rgb;
    //    fFragColor = texture(uTexture, vTexCoords).rgb;
}