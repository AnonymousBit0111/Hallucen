#pragma once

#include "Hallucen/vector.h"
#include "SDL2/SDL.h"
namespace Hallucen {
class Scene {

public:
  virtual void ImGuiLogic(float frametime) = 0;
  virtual void render() = 0;
  virtual void update(float deltaTime) = 0;
  virtual void winSizeChanged(Hallucen::Vector2i newsize) = 0;
  virtual void handleKey(SDL_Keycode key) = 0;

  virtual void onMouseDown(){}
};
} // namespace Hallucen