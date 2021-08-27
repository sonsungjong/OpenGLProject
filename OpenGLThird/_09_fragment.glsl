#version 330 core
out vec4 FragColor;

// uniform vec4 ourColor; // set in code during render
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mix;

void main() {
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mix);
} 