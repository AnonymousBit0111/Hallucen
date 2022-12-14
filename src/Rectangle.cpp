#include "Hallucen/Rectangle.h"
#include "Hallucen/GL/ElementBuffer.h"
#include "Hallucen/GL/Shader.h"
#include "Hallucen/GL/ShaderProgram.h"
#include "Hallucen/GL/VertexArray.h"
#include "Hallucen/GL/VertexBuffer.h"
#include "Hallucen/GL/gl.h"
#include "Hallucen/vector.h"
#include "fwd.hpp"

#include "ext/matrix_transform.hpp"

#include <iostream>
#include <string>
#include <vector>

using namespace Hallucen;
using namespace Hallucen::GL;

Rectangle::Rectangle(Vector2 size, Vector2 position)
    : m_Size(size), m_Position(position), m_VAO(),
      m_VBO(), m_EBO() {

  // will always be the same and will be copied into the VBO so it is useless
  // after ctor
  std::vector<unsigned int> indices = {0, 1, 2, 2, 3, 0};

  // can be calculated later
  std::vector<float> vertices = {
      0.0f,     0.0f,     // bottom left
      m_Size.x, 0.0f,     // bottom right
      m_Size.x, m_Size.y, // top right
      0.0f,     m_Size.y  // top left
  };

  m_ModelMatrix = glm::translate(glm::mat4(1.0f),
                                 glm::vec3(m_Position.x, m_Position.y, 0.0f));

  m_VAO.bind();
  m_VBO.bind();
  m_EBO.bind();

  m_VBO.fill(vertices);

  m_EBO.fill(indices);

  m_VAO.createAttribute(2, GL_FALSE, 2, 0);

  std::string vertexSource = R"(
#version 410
layout(location=0)in vec2 aPos;
layout(location=1)in vec2 aTexCoord;
out vec3 vColour;
uniform vec3 uColour;
uniform mat4 uViewProjectionMatrix;
uniform mat4 uModelMatrix;

out mat4 vModel;
out mat4 vViewProj;
out vec2 vTexCoord;
void main()
{
    gl_Position=uViewProjectionMatrix*uModelMatrix*vec4(aPos.xy,0,1);
    vColour = uColour;
    vTexCoord = aTexCoord;
    vModel = uModelMatrix;
    vViewProj = uViewProjectionMatrix;
}
)";

  std::string fragmentSource = R"(
#version 410
out vec4 FragColor;
in vec3 vColour;
in vec2 vTexCoord;
in mat4 vModel;
in mat4 vViewProj;

uniform sampler2D uTexture;
uniform vec2 ulightPos;
vec4 worldPos;



float getDistance(vec2 a, vec2 b){
  float totaldist = 0;
  float dX = abs(a.x -b.x);
  float dY = abs(a.y-b.y);
  totaldist = dX+dY;
  return totaldist;
  
}
void main()
{
  float lightIntensity = 150.0f;

  float lightlevel = ((1/distance(ulightPos,gl_FragCoord.xy))*lightIntensity)-0.001f;
    FragColor = vec4(vColour,1.0f)*lightlevel;

    
}

)";

  Shader vertexShader(GL_VERTEX_SHADER);
  Shader fragmentShader(GL_FRAGMENT_SHADER);

  vertexShader.load(vertexSource);
  if (!vertexShader.compile()) {
    char infoLog[512];

    glGetShaderInfoLog(vertexShader.getID(), 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  fragmentShader.load(fragmentSource);
  if (!fragmentShader.compile()) {
    char infoLog[512];

    glGetShaderInfoLog(fragmentShader.getID(), 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
    exit(-1);
  }
  m_ShaderProgram.attachShader(vertexShader.getID());
  m_ShaderProgram.attachShader(fragmentShader.getID());
  m_ShaderProgram.link();

  m_ShaderProgram.use();
  m_ShaderProgram.setVec3("uColour", {1.0f, 1.0f, 1.0f});
  m_ShaderProgram.setMat4("uModelMatrix", m_ModelMatrix);

  this->m_Data.IBO = &m_EBO;
  this->m_Data.VAO = &m_VAO;
  // this->m_Data.model = &m_ModelMatrix;
  this->m_Data.shader = &m_ShaderProgram;
}

void Rectangle::setLightPos(Vector2 pos) {
  m_ShaderProgram.use();
  m_ShaderProgram.setVec2("ulightPos", pos);
}
void Rectangle::setColour(Vector3 rgb) {
  m_ShaderProgram.use();
  m_ShaderProgram.setVec3("uColour", rgb);
}

Rectangle::~Rectangle() {}