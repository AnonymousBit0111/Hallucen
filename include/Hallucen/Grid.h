#pragma once

#include "Hallucen/Rect.h"
#include "Hallucen/vector.h"
#include <vector>
namespace Hallucen {
class Grid {
private:
  int m_rows, m_columns;
  float m_size;

  std::vector<Hallucen::Rect> m_rects;

public:
  Grid(int size, Vector2 winsize);
  void update();
  inline std::vector<Hallucen::Rect> *getRects() { return &m_rects; }
};
} // namespace Hallucen