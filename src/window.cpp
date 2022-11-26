#include "Hallucen/window.h"
#include "GLFW/glfw3.h"
#include "Hallucen/vector.h"

#include <cstdlib>
#include <iostream>
#include <memory>
using namespace Hallucen;

template <typename T> using Ref = std::shared_ptr<T>;

void Errorcallback(int errorcode, const char *description) {

  std::cout << "Error:\n";
  std::cout << errorcode << "\n";

  std::cout << description << "\n";
}

Window::Window(int width, int height, int x, int y)

{
  m_Position = {x, y};
  m_Size = {width, height};

  glfwSetErrorCallback(Errorcallback);

  initGlfwWindow(m_Size, m_Position, &m_GLFW_window);
  initGLAD();
}

void Window::run() {
  m_Open = true;
  glfwMakeContextCurrent(m_GLFW_window);
  while (!glfwWindowShouldClose(m_GLFW_window)) {
    glfwSwapBuffers(m_GLFW_window);
    glfwPollEvents();
  }
}

Ref<Window> Window::create(int width, int height, int x, int y) {

  return std::make_shared<Window>(Window(width, height, x, y));
}

void Window::initGlfwWindow(Vector2i size, Vector2i position,
                            GLFWwindow **window) {

  if (!glfwInit()) {
    exit(-1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  *window = glfwCreateWindow(size.x, position.y, "Hello World", NULL, NULL);
  glfwMakeContextCurrent(*window);

  if (!*window) {
    glfwTerminate();
    exit(-1);
  }
}

void Window::initGLAD() {
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    exit(-1);
  }
}

Window::~Window() { glfwDestroyWindow(m_GLFW_window); }