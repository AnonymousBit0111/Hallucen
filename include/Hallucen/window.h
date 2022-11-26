#pragma once

#include "Hallucen/vector.h"

#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace Hallucen {

class Window {

private:
  // members

  Hallucen::Vector2i m_Size;
  Hallucen::Vector2i m_Position;
  GLFWwindow *m_GLFW_window;
  bool m_Open;

private:
  // functions
  Window(int width, int height, int x, int y);
  static void initGlfwWindow(Hallucen::Vector2i size,Hallucen::Vector2i position,GLFWwindow **pwindow);
  static void initGLAD();

public:
  //  a private contructor is used by the create() method to contruct this
  //  object instead of 
  Window() = delete;

  // to be memory safe hallucen only uses shared pointers to objects

  static std::shared_ptr<Window> create(int width, int height, int x, int y);

  void run();

  ~Window();
};
} // namespace Hallucen