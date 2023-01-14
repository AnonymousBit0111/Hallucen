#version 410
out vec4 FragColor;
in vec3 vColour;
in vec2 vTexCoord;
in mat4 vViewProj;




uniform sampler2D uTex;

void main()
{
    // TODO add textures
    // FragColor = vec4(1.0f);
    FragColor = texture(uTex,vTexCoord);

}