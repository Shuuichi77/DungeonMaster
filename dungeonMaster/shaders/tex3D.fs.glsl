#version 330

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

uniform sampler2D uTexture;
uniform vec3 uLightPosition_vs;

out vec3 fFragColor;

void main() {
    vec3 normal = normalize(vNormal_vs);
    vec3 lightDir = normalize(uLightPosition_vs - vPosition_vs);
    float diff = max(dot(normal, lightDir), 0.0);
    float dist = distance(uLightPosition_vs, vPosition_vs);
    float att = min(1.0 / (dist * dist), 0.8); // min() prevent from too much attenuation if too close
    vec3 diffuse = vec3(diff * att);
    vec3 ambient = vec3(0.25);
    vec3 color = texture(uTexture, vTexCoords).rgb;

    fFragColor = (ambient + diffuse) * color;
}