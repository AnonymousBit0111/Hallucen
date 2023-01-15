#include "Hallucen/Hallucen.h"

#include "Editor/MainScene.h"

using namespace Hallucen;
int main() {
  Engine::init();
  Engine::initWindow(1024, 720, "Pathfinder");

  Engine::runScene(Hallucen::make_Ref<Editor::MainScene>());

  Engine::cleanup();
  return 0;
}
