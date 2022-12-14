#pragma once
#include "Hallucen/GL/Renderer.h"
#include "Hallucen/Image.h"
#include "Hallucen/vector.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <memory>
#include <string>
#include <iostream>
class Scene;
namespace Hallucen {

static GLFWwindow *window = nullptr;
static bool initialised = false;
static std::shared_ptr<GL::Renderer> renderer;

static Vector2i size;
static Vector2i frameBuffersize;

bool init();
bool initWindow(int width, int height, const std::string &name);

GLFWwindow *getWindow();

Vector2i getSize();
inline void setRenderer(std::shared_ptr<GL::Renderer> _renderer) {
  renderer = _renderer;
}
void Update(float deltaTime);

std::string loadFile(const std::string &path);

std::shared_ptr<Image> loadImage(const std::string &path);

void mainLoop();
void runScene(std::shared_ptr<Scene> scene);



void cleanup();

void frameBufferSizeCallback(GLFWwindow *win, int width, int height);
Vector2i getFrameBufferSize();
static inline void errorCallback(int error_code, const char *description) {

  std::cout << "GLFW Error: " << error_code << std::endl << description;
}

} // namespace Hallucen