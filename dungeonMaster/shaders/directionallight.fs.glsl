#version 330

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fFragColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

vec3 blinnPhong() {
    vec3 N = normalize(vNormal_vs);
    vec3 w0 = normalize(-vPosition_vs);
    vec3 wi = normalize(uLightDir_vs);
    vec3 halfVector = normalize(wi + w0) / 2.;
    float NdotL = max(dot(wi, N), 0.0);
    float NdotH = max(dot(halfVector, N), 0.0);
    float specular = pow(NdotH, uShininess);

    return uLightIntensity * (uKd * NdotL + uKs * specular);
}

void main() {
    fFragColor = blinnPhong();
}