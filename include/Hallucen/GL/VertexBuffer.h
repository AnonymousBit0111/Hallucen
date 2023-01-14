#pragma once

#include "Hallucen/GL/DrawData.h"
#include <vector>
namespace Hallucen {

namespace GL {
class VertexBuffer {
private:
  unsigned int m_ID;

public:
  VertexBuffer();
  void bind();
  static void unBind();
  void fill(std::vector<float> &data);
  void fill(std::vector<GL::Vertex> &data);
  void fill(std::vector<GL::TextureVertex> &data);



  void emplace(std::vector<float> &data, long offset);
  void emplace(std::vector<Vertex> &data, long offset);
  void emplace(std::vector<TextureVertex> &data, long offset);
  void emplace(Vertex vertex, long offset);
  void emplace(Vertex *data, long size, long offset);
  void reserve(unsigned int size);
  unsigned int getID();
  ~VertexBuffer();
};
} // namespace GL
} // namespace Hallucen