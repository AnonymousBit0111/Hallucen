#pragma once
#include "Hallucen.h"
#include "Hallucen/vector.h"
#include "fwd.hpp"
#include <vector>

namespace Hallucen {

// a rect that has texture coordinates and its origin is the upper left corner
class TexRect {
private:
  Vector2 m_Size;
  Vector2 m_Position;
  glm::vec3 m_Colour;
  std::vector<GL::TextureVertex> vertices;
  void updateVerts();

public:
  TexRect(Vector2 size, Vector2 position, Vector3 colour);
  inline std::vector<GL::TextureVertex> getVerts() { return vertices; }
  inline Vector2 getPosition() { return m_Position; }
  void setPosition(glm::vec2 pos);
  void setSize(glm::vec2 size);
  Vector2 getSize() { return m_Size; }
  bool contains(Vector2 pos);

  void setColour(Vector3 rgb);
  void move(glm::vec2 pos);
  void setTexCoords(std::vector<glm::vec2> &coords);

  std::vector<glm::vec2> getTexCoords();
  inline ~TexRect() {}
};
} // namespace Hallucen