#version 410

layout( location = 0 ) in vec4 Position;
layout( location = 2 ) in vec2 TexCoord; 


uniform mat4 ProjectionViewModel;
uniform mat4 ModelMatrix;

out vec4 vPosition;
out vec2 vTexCoord;

void main() {
	vPosition = ModelMatrix * Position;
	vTexCoord = TexCoord;
	gl_Position = ProjectionViewModel * Position;
}