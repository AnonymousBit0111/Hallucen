#pragma once
#include "Hallucen.h"
#include "Hallucen/GL/gl.h"
#include "Hallucen/vector.h"
#include "fwd.hpp"
namespace Hallucen {

class Rect {
private:
  Vector2 m_Size;
  Vector2 m_Position;
  Vector3 m_Colour;
  std::vector<GL::Vertex> vertices;
  void updateVerts();

public:
  Rect(Vector2 size, Vector2 position, Vector3 colour);
  inline std::vector<GL::Vertex> getVerts() { return vertices; }
  inline Vector2 getPosition() { return m_Position; }
  inline Vector3 getColour() { return m_Colour; }
  static inline std::vector<unsigned int> getIndices() {
    return {0, 1, 2, 2, 3, 0};
  };

  Vector2 getSize() { return m_Size; }
  bool contains(Vector2 pos);

  void setColour(Vector3 rgb);
  void move(glm::vec2 pos);
  void setSize(glm::vec2 size);
  void setPosition(glm::vec2 pos);
  inline ~Rect() {}
};
} // namespace Hallucen