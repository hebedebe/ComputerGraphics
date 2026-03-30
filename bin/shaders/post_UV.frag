// post-processing fragment shader
#version 410

in vec2 vTexCoord;

uniform sampler2D colourTarget;

out vec4 FragColour;

// just output the colour unchanged
vec4 Default(vec2 texCoord) 
{
    return texture( colourTarget, texCoord );
}

vec4 UV(vec2 texCoord) 
{
    return vec4(texCoord.rg, 0, 1);
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
    // FragColour = Default(texCoord);
    FragColour = UV(texCoord);
}