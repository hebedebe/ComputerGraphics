// post-processing fragment shader
#version 410

in vec2 vTexCoord;

uniform sampler2D colourTarget;

out vec4 FragColour;

vec4 BoxBlur(vec2 texCoord, float dist) {
    vec2 texel = 1.0f / textureSize(colourTarget, 0);
    // 9-tap box kernel
    vec4 colour = texture(colourTarget, texCoord);
    colour += texture(colourTarget, texCoord + texel * vec2(-dist,dist));
    colour += texture(colourTarget, texCoord + texel * vec2(-dist,0));
    colour += texture(colourTarget, texCoord + texel * vec2(-dist,-dist));
    colour += texture(colourTarget, texCoord + texel * vec2(0,dist));
    colour += texture(colourTarget, texCoord + texel * vec2(0,-dist));
    colour += texture(colourTarget, texCoord + texel * vec2(dist,dist));
    colour += texture(colourTarget, texCoord + texel * vec2(dist,0));
    colour += texture(colourTarget, texCoord + texel * vec2(dist,-dist));
    return colour / 9;
}

void main() 
{
    // calculate texel size
    vec2 texSize = textureSize( colourTarget, 0 );
    vec2 texelSize = 1.0f / texSize;
    // adjust texture coordinate
    vec2 scale = (texSize - texelSize) / texSize;
    vec2 texCoord = vTexCoord / scale + texelSize * 0.5f;
    // sample post effect
    FragColour = BoxBlur(texCoord, 1);
}