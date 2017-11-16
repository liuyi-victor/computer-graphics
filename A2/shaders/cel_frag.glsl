precision mediump float; // It is required to set a floating point precision in all fragment shaders.

// Interpolated values from vertex shader
varying vec3 normalInterp; // Normal
varying vec3 vertPos; // Vertex position

uniform float Ka;   // Ambient reflection coefficient
uniform float Kd;   // Diffuse reflection coefficient
uniform float Ks;   // Specular reflection coefficient
uniform float shininessVal; // Shininess

// Material color
uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform vec3 lightPos; // Light position

void main() 
{
	// Your solution should go here
	// Only the ambient colour calculations have been provided as an example.

	gl_FragColor = Ka * vec4(ambientColor, 1.0);

	// basically discretize the diffuse and specular components of the shading

	//diffuse reflection
	vec3 lightDirection = lightPos - vertPos;
	float resultdiffuse = dot(normalize(normalInterp), normalize(lightDirection));
	if(resultdiffuse > 0.2)
	{
		if(resultdiffuse > 0.8)
			gl_FragColor = gl_FragColor + Kd * vec4(diffuseColor, 1.0);
		else
			gl_FragColor = gl_FragColor + Kd * vec4(diffuseColor, 1.0) * 0.5;
	}

	//specular reflection
	vec3 reflection = 2.0*dot(normalize(normalInterp), lightDirection)*normalize(normalInterp) - lightDirection;
	float resultspecular = pow(max(0.0, dot(normalize(-vertPos), normalize(reflection))), shininessVal);
	if(resultspecular > 0.2)
	{
		if(resultspecular > 0.8)
			gl_FragColor = gl_FragColor + Ks * vec4(vec3(1.0), 1.0);
		else
			gl_FragColor = gl_FragColor + Ks * vec4(vec3(1.0), 1.0) * 0.5 ;
	}
}
