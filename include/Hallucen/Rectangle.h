#pragma once

#include "Hallucen/GL/ElementBuffer.h"
#include "Hallucen/GL/ShaderProgram.h"
#include "Hallucen/GL/VertexArray.h"
#include "Hallucen/GL/VertexBuffer.h"
#include "Hallucen/GL/gl.h"
#include "Hallucen/vector.h"
namespace Hallucen {

class Rectangle {

private:
  GL::VertexArray m_VAO;
  GL::VertexBuffer m_VBO;
  GL::ElementArrayBuffer m_EBO;
  GL::ShaderProgram m_ShaderProgram;
  glm::mat4 m_ModelMatrix;

  GL::DrawData m_Data;

  Vector2 m_Size;
  Vector2 m_Position;

  void updateData();

public:
  Rectangle(Vector2 size,Vector2 position);
  inline const GL::DrawData getData() { return m_Data; }
  void setLightPos(Vector2 pos);
  void setColour(Vector3 rgb);
  ~Rectangle();
};
} // namespace Hallucen