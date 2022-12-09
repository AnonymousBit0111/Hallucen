#pragma once
#include "Hallucen.h"
#include "Hallucen/GL/gl.h"
#include "Hallucen/vector.h"
namespace Hallucen {

class Rect {
private:
  Vector2 m_Size;
  Vector2 m_Position;
  Vector3 m_Colour;
  std::vector<GL::Vertex> vertices;

public:
  Rect(Vector2 size, Vector2 position, Vector3 colour);
  inline std::vector<GL::Vertex> getVerts() { return vertices; }
  inline Vector2 getPosition() { return m_Position; }
  bool contains(Vector2 pos);

  void setColour(Vector3 rgb);
  void setPosition(Vector2 pos);
  inline Vector2 getSize() { return m_Size; }
  inline ~Rect() {}
};
} // namespace Hallucen