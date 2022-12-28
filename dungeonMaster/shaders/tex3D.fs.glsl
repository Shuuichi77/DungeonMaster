#version 330

in vec3 vPosition_vs;
in vec3 vNormal_vs;
in vec2 vTexCoords;

uniform sampler2D uTexture;
uniform vec3 uLightPosition_vs;

uniform bool uIsAModel = false;
uniform bool uModelHasTexture = false;
uniform sampler2D uModelTexture;
uniform vec3 uModelColor;

out vec3 fFragColor;

void main() {

    vec3 color;
    if (uIsAModel) {
        if (uModelHasTexture) {
            color = texture(uModelTexture, vTexCoords).rgb;
        } else {
            color = uModelColor;
        }
    } else {
        color = texture(uTexture, vTexCoords).rgb;
    }

    vec3 normal = normalize(vNormal_vs);
    vec3 lightDir = normalize(uLightPosition_vs - vPosition_vs);
    float diff = max(dot(normal, lightDir), 0.0);

    float dist = distance(uLightPosition_vs, vPosition_vs);
    float attenuation = min(1.0 / (dist * dist), 0.80); // min() prevent from too much attenuation if too close

    vec3 diffuse = vec3(diff * attenuation);
    vec3 ambient = vec3(0.25);

    fFragColor = (ambient + diffuse) * color;
}