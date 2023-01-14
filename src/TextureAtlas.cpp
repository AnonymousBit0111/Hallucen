#include "Hallucen/TextureAtlas.h"
#include "Hallucen/Rect.h"
#include "Hallucen/TexRect.h"
#include "Hallucen/vector.h"
#include "fwd.hpp"
#include <cassert>
#include <memory>
#include <utility>
#include <vector>
using namespace Hallucen;

TextureAtlas::TextureAtlas(std::shared_ptr<Hallucen::Image> img) {
  this->img = img;
}

void TextureAtlas::addTex(std::string str, std::vector<glm::vec2> coords) {

  for (auto &i : coords) {
    i.x /= img->width;
    i.y /= img->height;
    
  }
  map.insert(std::make_pair(str, coords));
}

std::vector<glm::vec2> TextureAtlas::getTex(std::string str) {
  if (map.contains(str)) {
    return map.at(str);
  } else {
    assert(false);
  }
}

std::vector<glm::vec2> TextureAtlas::operator[](std::string &str) {
  return getTex(str);
}

TextureAtlas::~TextureAtlas() {}