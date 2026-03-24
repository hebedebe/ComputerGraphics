// a normal map fragment shader
#version 410

in vec2 vTexCoord;
in vec3 vNormal; 
in vec3 vTangent;
in vec3 vBiTangent;
in vec4 vPosition;

out vec4 FragColour;

uniform sampler2D diffuseTexture; // base texture
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;  // normal map texture

uniform vec3 Ka; // material ambient
uniform vec3 Kd; // material diffuse
uniform vec3 Ks; // material specular
uniform float specularPower;

uniform vec3 AmbientColour; // light ambient
uniform vec3 LightColour; // light colour - Id
uniform vec3 LightDirection;
const int MAX_LIGHTS = 16;
uniform int numLights;
uniform vec3 PointLightColour[MAX_LIGHTS];
uniform vec3 PointLightPosition[MAX_LIGHTS];

uniform vec3 CameraPosition;

vec3 getDiffuse(vec3 direction, vec3 colour, vec3 normal)
{
    return colour * max( 0, dot( normal, -direction ) );
}

vec3 getSpecular(vec3 direction, vec3 colour, vec3 normal, vec3 view)
{
    vec3 R = reflect( direction, normal );
    float specularTerm = pow( max( 0, dot( R, view ) ), specularPower ); // specularPower is Ns
    return specularTerm * colour;
}

void main() {

    vec3 N = normalize(vNormal); 
    vec3 T = normalize(vTangent);
    vec3 B = normalize(vBiTangent);
    vec3 L = normalize(LightDirection);

    mat3 TBN = mat3(T, B, N);

    vec3 texDiffuse = texture( diffuseTexture, vTexCoord ).rgb;
    vec3 texSpecular = texture( specularTexture, vTexCoord ).rgb; 
    vec3 texNormal = texture( normalTexture, vTexCoord ).rgb;
    
	N = TBN * (texNormal * 2 - 1);
	// calculate diffuse lighting from sunlight
    vec3 diffuseTotal = getDiffuse(L, LightColour, N);
    // calculate view vector
    vec3 V = normalize(CameraPosition - vPosition.xyz);
    // calculate specular light from directional light
    vec3 specularTotal = getSpecular(L, LightColour, N, V);
    // calculate each light property

	for (int i = 0; i < numLights; i++)
	{
		vec3 direction = vPosition.xyz - PointLightPosition[i];
		float distance = length(direction);
		direction = direction/distance;

		// attenuate the light intensity with inverse square law
		vec3 colour = PointLightColour[i]/ max(distance * distance, 0.01);
		diffuseTotal += getDiffuse(direction, colour, N);
		specularTotal += getSpecular(direction, colour, N, V);
	}

    vec3 ambient = AmbientColour * Ka * texDiffuse;
    vec3 diffuse = Kd * texDiffuse * diffuseTotal;
    vec3 specular = Ks * texSpecular * specularTotal * LightColour;

	FragColour = vec4(ambient + diffuse + specular, 1);
}