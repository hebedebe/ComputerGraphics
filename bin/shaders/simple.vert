// a simple shader
#version 410

layout( location = 0 ) in vec4 Position;

uniform mat4 ProjectionViewModel;

out vec4 clipSpacePos;
out vec4 position;

void main() {
	gl_Position = ProjectionViewModel * Position;
      clipSpacePos = gl_Position;
      position = Position;
}