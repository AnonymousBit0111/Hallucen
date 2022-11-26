#version 410
out vec4 FragColor;
in vec3 vColour;
in vec2 vTexCoord;

uniform sampler2D uTexture;
uniform vec2 ulightPos;

float getDistance(vec2 a, vec2 b){
  float totaldist = 0;
  float dX = abs(a.x -b.x);
  float dY = abs(a.y-b.y);
  totaldist = dX+dY;
  return totaldist;
  
}
void main()
{


    FragColor = vec4(1.0f)*(1/getDistance(ulightPos,gl_FragCoord.xy));
}