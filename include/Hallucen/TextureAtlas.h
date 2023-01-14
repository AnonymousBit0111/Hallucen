#pragma once

#include "Hallucen/Image.h"
#include "Hallucen/Rect.h"
#include "TexRect.h"
#include "fwd.hpp"
#include <map>
#include <memory>
#include <string>
#include <vector>
namespace Hallucen {

// contains the texture coordinates for textures, in normalised device coords.
class TextureAtlas {

private:
// coords are always labeled from the bottom left going anticlockwise up
  std::map<std::string, std::vector<glm::vec2>> map;
  std::shared_ptr<Hallucen::Image> img;

public:
  TextureAtlas(std::shared_ptr<Hallucen::Image> img);
  void addTex(std::string, std::vector<glm::vec2>);
  std::vector<glm::vec2> getTex(std::string str);

  std::vector<glm::vec2> operator[](std::string &str);

  ~TextureAtlas();
};

} // namespace Hallucen