#version 410
layout(location=0)in vec2 aPos;
layout(location=1)in vec3 aColour;
layout (location =2) in vec2 aTexCoord;

out vec3 vColour;
out vec2 vTexCoord;
uniform mat4 uViewProjectionMatrix;

out mat4 vViewProj;
void main()
{
    // TODO add rotation using model matrix
    
    gl_Position=uViewProjectionMatrix*vec4(aPos.xy,0,1);

    
    vViewProj=uViewProjectionMatrix;
    vColour=aColour;
    vTexCoord = aTexCoord;
}