#pragma once

#include <vector>
namespace Hallucen {

namespace GL {

class ElementArrayBuffer {
private:
  unsigned int m_ID;
  unsigned int m_Size = 0;

public:
  ElementArrayBuffer();
  void fill(std::vector<unsigned int> data);
  inline unsigned int getSize() { return m_Size; }
  void bind();
  static void unBind();
  ~ElementArrayBuffer();
};

} // namespace GL
} // namespace Hallucen