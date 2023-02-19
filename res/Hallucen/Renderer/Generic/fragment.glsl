#version 450
out vec4 FragColor;
in vec3 vColour;
in vec2 vTexCoord;
in mat4 vViewProj;

layout (location = 0) out vec4 outFragColor;


uniform sampler2D uTex;

void main()
{
    // TODO add textures
    // FragColor = vec4(1.0f);
    outFragColor = vec4(vColour,1.0f);
    // outFragColor = texture(uTex,vTexCoord);

}