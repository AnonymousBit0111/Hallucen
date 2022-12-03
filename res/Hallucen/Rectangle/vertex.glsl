#version 410
layout(location=0)in vec2 aPos;
layout(location=1)in vec3 aColour;
out vec3 vColour;
uniform vec3 uColour;
uniform mat4 uViewProjectionMatrix;

out mat4 vModel;
out mat4 vViewProj;
void main()
{
    gl_Position=uViewProjectionMatrix*vec4(aPos.xy,0,1);
    vViewProj = uViewProjectionMatrix;
    vColour= aColour;
}