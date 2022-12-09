#include "Hallucen/Grid.h"
#include "Hallucen/GL/Renderer.h"
#include "Hallucen/Rect.h"
#include "Hallucen/vector.h"

#include <math.h>
using namespace Hallucen;
using namespace Hallucen::GL;

Grid::Grid(int size, Vector2 winsize) {
  m_columns = std::round(winsize.x / size);
  m_rows = std::round(winsize.y / size);

  m_rects.reserve(m_rows * m_columns);
  Renderer::beginQuadBatch();
  for (int c = 0; c < m_columns; c++) {
    for (int r = 0; r < m_rows; r++) {
      Rect rect({1.0f * size, 1.0f * size}, {1.0f * c * size, 1.0f * r * size},
                {1, 1, 1});
      Renderer::addRect(rect);
      m_rects.push_back(rect);
    }
  }
  Renderer::endQuadBatch();
}

void Grid::update() {
  Renderer::beginQuadBatch();
  for (auto &i : m_rects) {
    Renderer::addRect(i);
  }
  Renderer::endQuadBatch();
}