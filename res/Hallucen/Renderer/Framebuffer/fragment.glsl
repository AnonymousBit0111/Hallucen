#version 410
out vec4 FragColor;
in vec3 vColour;
in vec2 vTexCoord;
in mat4 vViewProj;

uniform sampler2D tex;

void main()
{
    // TODO add textures
    
    FragColor=texture(tex,vTexCoord);
    
}