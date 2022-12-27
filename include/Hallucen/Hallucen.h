#pragma once
#include "Hallucen/GL/Renderer.h"
#include "Hallucen/Image.h"
#include "Hallucen/vector.h"
#include "SDL2/SDL.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <memory>
#include <string>
class Scene;
namespace Hallucen {

class Engine {
public:
  static bool init();
  static bool initWindow(int width, int height, const std::string &name);

  static SDL_Window *getWindow();

  static Vector2i getSize();
  static inline void setRenderer(std::shared_ptr<GL::Renderer> _renderer);
  static void Update(float deltaTime);

  static std::string loadFile(const std::string &path);

  static std::shared_ptr<Image> loadImage(const std::string &path);

  static void mainLoop();
  static void runScene(std::shared_ptr<Scene> scene);

  static void cleanup();

  static void frameBufferSizeCallback(GLFWwindow *win, int width, int height);
  static Vector2i getFrameBufferSize();
  static inline void errorCallback(int error_code, const char *description) {

    std::cout << "GLFW Error: " << error_code << std::endl << description;
  }
};

} // namespace Hallucen