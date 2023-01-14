#pragma once

#include "Hallucen/GL/DrawData.h"
#include "SDL2/SDL_rect.h"
#include <vector>
namespace Hallucen {

std::vector<Hallucen::GL::TextureVertex> getRectVertices(SDL_Rect rect);
}