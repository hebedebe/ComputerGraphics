// a simple flat colour shader
#version 410

in vec4 clipSpacePos;
in vec4 position;

out vec4 FragColour;

void main() {

	FragColour = sin(position);
}