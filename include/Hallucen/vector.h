#pragma once

#include "glm.hpp"
namespace Hallucen {
struct Vector2 {
  float x, y;

  inline operator glm::vec2() { return glm::vec2(x, y); }
};

struct Vector2i {
  int x, y;
};
struct Vector3 {
  float x, y, z;
};

} // namespace Hallucen