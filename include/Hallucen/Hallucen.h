#pragma once
#include "Hallucen/GL/Renderer.h"
#include "Hallucen/Image.h"
#include "Hallucen/vector.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>
#include <iostream>
class Scene;
namespace Hallucen {

static GLFWwindow *window = nullptr;
static bool initialised = false;
static std::shared_ptr<GL::Renderer> renderer;

static Vector2 size;

bool init();
bool initWindow(int width, int height, const std::string &name);

GLFWwindow *getWindow();

Vector2 getSize();
inline void setRenderer(std::shared_ptr<GL::Renderer> _renderer) {
  renderer = _renderer;
}
void Update(float deltaTime);

std::string loadFile(const std::string &path);

std::shared_ptr<Image> loadImage(const std::string &path);

void mainLoop();
void runScene(Scene scene);



void cleanup();

void frameBufferSizeCallback(GLFWwindow *win, int width, int height);
static inline void errorCallback(int error_code, const char *description) {

  std::cout << "Error: " << error_code << std::endl << description;
}

} // namespace Hallucen