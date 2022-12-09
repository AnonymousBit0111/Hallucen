#pragma once
#include "Hallucen/GL/RenderBuffer.h"
#include "Hallucen/GL/Texture2D.h"
#include <memory>
namespace Hallucen::GL {

class Framebuffer {
  unsigned int m_ID = 0;
  unsigned int m_Width, m_Height;
  std::shared_ptr<Texture2D> m_ColourAtachment;


  // whether the buffer is just the screen or not
  bool m_SwapChainTarget = false;

private:
public:
  Framebuffer(unsigned int width, unsigned int height);
  void attachTexture2D(std::shared_ptr<Texture2D> tex);
  void attachRenderBuffer(RenderBuffer buffer);
  void blit(unsigned int DrawfboID);
  bool isComplete();
  void bind();
  void unBind();

  inline unsigned int getID(){return m_ID;}
  ~Framebuffer();
};
} // namespace Hallucen::GL