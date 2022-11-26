#pragma once

#include <vector>
namespace Hallucen {

namespace GL {

class VertexBuffer {
private:
  unsigned int m_ID;
  std::vector<float> m_Vertices;

public:
  VertexBuffer();
  void bind();
  static void unBind();
  void fill(std::vector<float> data);
  unsigned int getID();
  ~VertexBuffer();
};
} // namespace GL
} // namespace Hallucen