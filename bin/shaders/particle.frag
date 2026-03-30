#version 410

in vec4 vPosition;
in vec2 vTexCoord;

uniform vec4 colour;

out vec4 FragColour;

void main() 
{
    float dist = distance(vTexCoord, vec2(0.5, 0.5));

    FragColour = 1-vec4(dist);
    // FragColour = colour;
}