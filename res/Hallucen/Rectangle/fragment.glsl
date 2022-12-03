#version 410
out vec4 FragColor;
in vec3 vColour;
in mat4 vModel;
in mat4 vViewProj;




void main()
{

    FragColor = vec4(vColour,1.0f);
    
    
}