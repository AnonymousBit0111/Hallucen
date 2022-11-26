#version 410
layout(location=0)in vec2 aPos;
layout(location=1)in vec3 aColour;
layout(location=2)in vec2 aTexCoord;
out vec3 vColour;
uniform vec3 uColour;
uniform mat4 uViewProjMatrix;
uniform mat4 uModelMatrix;

out vec2 vTexCoord;
void main()
{
    
    gl_Position=uViewProjMatrix*uModelMatrix*vec4(aPos.xy,0,1);
    // gl_Position = vec4(aPos.xy,0,1);
    vColour=aColour;
    vTexCoord=aTexCoord;
}