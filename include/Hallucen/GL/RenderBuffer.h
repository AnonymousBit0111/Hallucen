#pragma once

namespace Hallucen::GL {
class RenderBuffer {

private:
  unsigned int m_ID;

public:
  RenderBuffer();
  RenderBuffer(unsigned int width, unsigned int height);
  void bind();
  unsigned int getID() { return m_ID; }
  void unBind();
  ~RenderBuffer();
};
} // namespace Hallucen::GL