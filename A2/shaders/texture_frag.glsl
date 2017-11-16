precision mediump float;  // It is required to set a floating point precision in all fragment shaders.

// Interpolated values from vertex shader
varying highp vec2 texCoordInterp;

// uniform values are the same across the scene
uniform sampler2D uSampler;	// A GLSL sampler represents a single texture. A sampler2D can be used to sample a 2D texture.

void main() 
{
	highp vec2 comple = vec2(texCoordInterp.x, 1.0 - texCoordInterp.y);	// makes the inverted global upright

	// use texture2D to determine the color of the pixels based on the interpolated texture coordinates
	gl_FragColor = texture2D(uSampler, comple);				
}
