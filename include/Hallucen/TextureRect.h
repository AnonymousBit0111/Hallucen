#pragma once

#include "Hallucen/GL/gl.h"
#include "Hallucen/vector.h"
#include <vector>

namespace Hallucen {

class TextureRect {
private:
  Vector2 m_Size;
  Vector2 m_Position;
  std::vector<GL::Vertex> vertices;

public:
  TextureRect(Vector2 size, Vector2 position, Vector3 colour);
  inline ~TextureRect() {}
};
} // namespace Hallucen