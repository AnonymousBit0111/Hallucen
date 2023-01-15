#pragma once
#include "Hallucen/GL/Renderer.h"
#include "Hallucen/Image.h"
#include "Hallucen/vector.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_keycode.h"
#include "fwd.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <memory>
#include <string>
namespace Hallucen {
class Scene;

class Engine {
public:
  static bool init();
  static bool initWindow(int width, int height, const std::string &name);

  static SDL_Window *getWindow();
  static bool isKeyDown(SDL_Keycode key);
  static Vector2i getSize();
  static inline void setRenderer(std::shared_ptr<GL::Renderer> _renderer);
  static void Update(float deltaTime);

  static std::string loadFile(const std::string &path);

  static std::shared_ptr<Image> loadImage(const std::string &path);

  static void mainLoop();
  static void runScene(std::shared_ptr<Hallucen::Scene> scene);

  static void cleanup();

  static glm::vec2 getMousePosition();

  static void frameBufferSizeCallback(GLFWwindow *win, int width, int height);
  static Vector2i getFrameBufferSize();
  static inline void errorCallback(int error_code, const char *description) {

    std::cout << "GLFW Error: " << error_code << std::endl << description;
  }
};

} // namespace Hallucen