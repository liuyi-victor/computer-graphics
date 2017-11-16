precision mediump float; // It is required to set a floating point precision in all fragment shaders.

// Interpolated values from vertex shader
varying vec3 normalInterp; // Normal
varying vec3 vertPos; // Vertex position
varying vec3 viewVec; // View vector (eye to fragment)

uniform float Ka;   // Ambient reflection coefficient
uniform float Kd;   // Diffuse reflection coefficient
uniform float Ks;   // Specular reflection coefficient
uniform float shininessVal; // Shininess

// Material color
// HINT: Use the environment map as the ambient color
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform vec3 lightPos; // Light position

uniform samplerCube envTexSampler; // A GLSL sampler represents a single texture. A samplerCube can be used to sample a cubemap texture.

void main() 
{
	/* use environment map as the ambient color:
		1. determine the reflection of the view vector at a point of the surface (similar to ray tracing)
		2. determine the intersection of this reflected ray with the environment cube using textureCube()
	*/
	vec3 reflectedDirection = reflect(viewVec, normalize(normalInterp));
	gl_FragColor = textureCube(envTexSampler, reflectedDirection);

	// diffuse shading
	vec3 lightDirection = lightPos - vertPos;
	gl_FragColor = gl_FragColor + Kd * vec4(diffuseColor, 1.0) * max(0.0, dot(normalize(normalInterp), normalize(lightDirection)));
	
	// specular shading
	vec3 reflection = 2.0*dot(normalize(normalInterp), lightDirection)*normalize(normalInterp) - lightDirection;
	gl_FragColor = gl_FragColor + Ks * vec4(specularColor, 1.0) *  pow(max(0.0, dot(normalize(-vertPos), normalize(reflection))), shininessVal);
}
