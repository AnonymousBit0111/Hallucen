#pragma once
#include "Hallucen/GL/Renderer.h"
#include "Hallucen/Image.h"
#include "Hallucen/vector.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <string>
namespace Hallucen {
typedef void (*UpdateFunction)(float deltaTime);
typedef void (*RenderFunction)();
typedef void (*ImGuiLogic)(float deltaTime);

static GLFWwindow *window = nullptr;
static bool initialised = false;
static UpdateFunction UpdateFunc = nullptr;
static RenderFunction RenderFunc = nullptr;
static ImGuiLogic ImGuilogic = nullptr;
static std::shared_ptr<GL::Renderer> renderer;

static Vector2 size;

bool init();
bool initWindow(int width, int height, const std::string &name);

GLFWwindow *getWindow();

void setUpdateFunc(UpdateFunction func);
void setImGuiFunc(ImGuiLogic func);
void setRenderFunction(RenderFunction func);
Vector2 getSize();
inline void setRenderer(std::shared_ptr<GL::Renderer> _renderer) {
  renderer = _renderer;
}
void Update(float deltaTime);

std::string loadFile(const std::string &path);

std::shared_ptr<Image> loadImage(const std::string &path);

void mainLoop();

void cleanup();

void frameBufferSizeCallback(GLFWwindow *win, int width, int height);

} // namespace Hallucen