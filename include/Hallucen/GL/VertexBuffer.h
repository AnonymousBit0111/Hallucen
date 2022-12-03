#pragma once

#include <vector>
namespace Hallucen {

namespace GL {
struct Vertex;
class VertexBuffer {
private:
  unsigned int m_ID;

public:
  VertexBuffer();
  void bind();
  static void unBind();
  void fill(std::vector<float> &data);
  void fill(std::vector<Vertex> &data);
  void emplace(std::vector<float> &data, long offset);
  void emplace(std::vector<Vertex> &data, long offset);
  void emplace(Vertex vertex, long offset);
  void emplace(Vertex *data, long size, long offset);
  void reserve(unsigned int size);
  unsigned int getID();
  ~VertexBuffer();
};
} // namespace GL
} // namespace Hallucen