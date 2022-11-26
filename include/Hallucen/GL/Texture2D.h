#pragma once
#include "Hallucen/Image.h"
namespace Hallucen {
namespace GL {
class Texture2D {
private:
  unsigned int m_ID;

public:
  Texture2D();
  void bind(unsigned int slot);
  static void unBind();
  inline unsigned int getID() const { return m_ID; }
  void setImage(Hallucen::Image &image);
  void genMipmap();
  ~Texture2D();
};
} // namespace GL
} // namespace Hallucen