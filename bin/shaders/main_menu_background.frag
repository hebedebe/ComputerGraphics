// post-processing fragment shader
#version 410

in vec2 vTexCoord;

uniform float Time;

out vec4 FragColour;

void main() 
{
    float strength = sin(distance(vTexCoord, vec2(0.5)) + Time) + 1;

    FragColour = vec4(vec4(strength * 0.5) - distance(vTexCoord, vec2(0.5)));
}

