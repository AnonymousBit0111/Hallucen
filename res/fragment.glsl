#version 410
out vec4 FragColor;
in vec3 vColour;
in vec2 vTexCoord;

uniform sampler2D uTexture;
uniform sampler2D uTexture2;
void main()
{
 FragColor = mix(texture(uTexture,vTexCoord),texture(uTexture2,vTexCoord),0.2)*vec4(vColour,1.0);
 //FragColor = vec4(vColour,1.0);
}

