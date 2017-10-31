attribute vec3 position; // Given vertex position in object space
attribute vec3 normal; // Given vertex normal in object space

uniform mat4 projection, modelview, normalMat; // Given scene transformation matrices

// These will be given to the fragment shader and interpolated automatically
varying vec3 normalInterp;
varying vec3 vertPos;
varying vec4 color;

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
	// Your solution should go here.
	// Only the ambient colour calculations have been provided as an example.

	vec4 vertPos4 = modelview * vec4(position, 1.0);
	gl_Position = projection * vertPos4;
	color = Ka * vec4(ambientColor, 1.0); 

	// diffuse color
	vec4 normal_view = modelview * normalMat * vec4(normal, 1.0);
	color = color + Kd * vec4(diffuseColor, 1.0) * max(dot(normal_view, vec4(lightPos, 1.0)), 0.0); 

	// specular color
	vec4 reflection = reflect(-normalize(vec4(lightPos, 1.0)), normalize(normal_view));
	// reflect(vec4(lightPos, 1.0), vec4(normalize(normal),1.0))
	vec4 view;
	view = -vertPos4;
	//view.w = 1.0;
	color = color + Ks * vec4(specularColor, 1.0) * pow(       max( dot(reflection, view),  0.0  )          ,         shininessVal); 

	vertPos = gl_Position.xyw;
	//normalInterp = normalize(normalMat * vec4(normal, 1.0)).xyw;
	normalInterp = normalize(normal_view).xyw;
}
