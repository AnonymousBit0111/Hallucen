#pragma once

#include "Hallucen/GL/DrawData.h"
#include "Hallucen/GL/Texture2D.h"
#include "Hallucen/GL/gl.h"
#include "Hallucen/Image.h"
#include <cstddef>
#include <memory>
#include <vector>
namespace Hallucen {
class Drawable {
public:
  virtual std::shared_ptr<Image> getImage() = 0;
  virtual std::vector<GL::TextureVertex> getVertices() = 0;
  virtual std::vector<unsigned int> getIndices() = 0;
  virtual std::shared_ptr<GL::Texture2D> getTexture() = 0;
};
} // namespace Hallucen