#version 140
#define MAX_LIGHTS 64

smooth in vec3 fragmentPosition;
smooth in vec3 fragmentNormal;
smooth in vec2 fragTexCoord;
out vec4 color;

uniform vec3 camPosition;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
    float alpha;
};

struct TextureData {
    sampler2D diffuseMap;
    sampler2D specularMap;
    sampler2D shininessMap;
    sampler2D alphaMap;
    sampler2D normalMap;

    bool useDiffuseMap;
    bool useSpecularMap;
    bool useShininessMap;
    bool useAlphaMap;
    bool useNormalMap;
};

struct Light {
    int type; // 0 = directional, 1 = point, 2 = spotlight

    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float range;
    float angle;
    float exponent;
    bool dim;
};

struct Fog {
    int enabled;
    float start;
    float end;
    vec4 color;
};

uniform vec3 worldAmbient;
uniform Material material;
uniform TextureData textureData;
uniform Light lights[MAX_LIGHTS];
uniform int numLights;
uniform Fog fog;

uniform bool isTextLabel;

vec3 calculateDirectionalL(Light light, vec3 fragmentPosition, vec3 fragmentNormal, vec3 ambient, vec3 diffuse, vec3 specular, float shininess) {
    vec3 L = normalize(-light.direction);
    vec3 V = normalize(camPosition - fragmentPosition);
    vec3 R = reflect(-L, fragmentNormal);

    vec3 resColor = vec3(0.0f);
    resColor += ambient * light.ambient;
    resColor += diffuse * light.diffuse * max(dot(L, fragmentNormal), 0.0f);

    if (dot(L, fragmentNormal) > 0.0f && shininess > 0.01f) {
        resColor += specular * light.specular * pow(max(dot(R, V), 0.0f), shininess);
    }

    return resColor;
}

vec3 calculatePointL(Light light, vec3 fragmentPosition, vec3 fragmentNormal, vec3 ambient, vec3 diffuse, vec3 specular, float shininess) {
    float dist = distance(fragmentPosition, light.position);

    if (dist > light.range) {
        return vec3(0.0f);
    }

    vec3 L = normalize(light.position - fragmentPosition);
    vec3 R = reflect(-L, fragmentNormal);
    vec3 V = normalize(camPosition - fragmentPosition);

    vec3 resColor = vec3(0.0f);
    resColor += ambient * light.ambient;
    resColor += diffuse * light.diffuse * max(dot(L, fragmentNormal), 0.0f);

    if (dot(L, fragmentNormal) > 0.0f && shininess > 0.01f) {
        resColor += specular * light.specular * pow(max(dot(R, V), 0.0f), shininess);
    }

    if (light.dim) {
        float dimCoeff = clamp(1.0f - (dist / light.range), 0.0f, 1.0f);
        resColor *= dimCoeff;
    }

    return resColor;
}

vec3 calculateSpotL(Light light, vec3 fragmentPosition, vec3 fragmentNormal, vec3 ambient, vec3 diffuse, vec3 specular, float shininess) {
    float dist = distance(fragmentPosition, light.position);
    if (dist > light.range) {
        return vec3(0.0f);
    }

    vec3 L = normalize(light.position - fragmentPosition);
    vec3 R = reflect(-L, fragmentNormal);
    vec3 V = normalize(camPosition - fragmentPosition);

    vec3 resColor = vec3(0.0f);
    float alpha_angle = dot(-L, normalize(light.direction));
    float spotlightEffect = pow(max(alpha_angle, 0.0), light.exponent);

    resColor += ambient * light.ambient;

    float cutoff = cos(radians(light.angle));
    if (alpha_angle >= cutoff) {
        resColor += diffuse * light.diffuse * max(dot(L, fragmentNormal), 0.0) * spotlightEffect;

        if (dot(L, fragmentNormal) > 0.0 && shininess > 0.01f) {
            resColor += specular * light.specular * pow(max(dot(R, V), 0.0), shininess) * spotlightEffect;
        }
    }

    if (light.dim) {
        float distanceDimming = clamp(1.0 - (dist / light.range), 0.0, 1.0);
        resColor *= distanceDimming;
    }

    return resColor;
}

vec3 calculateLight(Light light, vec3 fragmentPosition, vec3 fragmentNormal, vec3 ambient, vec3 diffuse, vec3 specular, float shininess) {
    if (light.type == 0) {
        return calculateDirectionalL(light, fragmentPosition, fragmentNormal, ambient, diffuse, specular, shininess);
    } else if (light.type == 1) {
        return calculatePointL(light, fragmentPosition, fragmentNormal, ambient, diffuse, specular, shininess);
    } else if (light.type == 2) {
        return calculateSpotL(light, fragmentPosition, fragmentNormal, ambient, diffuse, specular, shininess);
    }

    return vec3(0.0f);
}

vec4 applyFog(vec4 color) {
    float dist = length(camPosition-fragmentPosition);

    float fogCoeff = (fog.end - dist) / (fog.end - fog.start);
    fogCoeff = clamp(fogCoeff, 0.0, 1.0);

    if (isTextLabel) {
        return vec4(mix(fog.color.rgb, color.rgb, fogCoeff), color.a); // text wont convert it to transparent
    }

    return mix(fog.color, color, fogCoeff); // fog will make it fully non-transparent
}

void main() {
    vec3 normalizedNormal = normalize(fragmentNormal); // :)

    vec3 ambient = material.ambient;
    vec3 diffuse = material.diffuse;
    vec3 specular = material.specular;
    float shininess = material.shininess;
    float alpha = material.alpha;

    if (textureData.useDiffuseMap) {
        vec4 texColor = texture(textureData.diffuseMap, fragTexCoord);
        if (texColor.a < 0.01) { discard; } // remove transparent bgr

        if (isTextLabel) { // text label
            diffuse = texColor.rgb * material.diffuse;
            ambient = diffuse * 0.25;
            alpha = texColor.r;
        } else { // images (image textures)
            diffuse = texColor.rgb;
            ambient = diffuse * 0.25;
            alpha = texColor.a * material.alpha;
        }
    }

    if (textureData.useSpecularMap) { specular = texture(textureData.specularMap, fragTexCoord).rgb; }
    if (textureData.useShininessMap) { shininess = texture(textureData.shininessMap, fragTexCoord).r; }
    if (textureData.useAlphaMap) { alpha = texture(textureData.alphaMap, fragTexCoord).r; }

    vec3 resultColor = ambient * worldAmbient; // default color is 1/4 of ambient
    for (int i = 0; i < numLights; ++i) {
        resultColor += calculateLight(lights[i], fragmentPosition, normalizedNormal, ambient, diffuse, specular, shininess);
    }

    color = vec4(resultColor, alpha);

    if (fog.enabled == 1) { color = applyFog(color); }
}