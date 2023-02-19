
#include "Hallucen/Hallucen.h"
#include "GLFW/glfw3.h"
#include "Hallucen/GL/Camera2D.h"
#include "Hallucen/GL/Renderer.h"
#include "Hallucen/Image.h"
#include "Hallucen/Profile.h"
#include "Hallucen/Ref.h"
#include "Hallucen/Scene.h"
#include "Hallucen/Stopwatch.h"
#include "Hallucen/vector.h"
#include "Hallucen/vk.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_keycode.h"
#include "SDL2/SDL_mouse.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include "SDL2/SDL_vulkan.h"
#include "fwd.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_sdl.h"
#include "imgui_impl_sdl.h"
#include "tracy/Tracy.hpp"
#include "vulkan/vulkan_core.h"
#include <SDL2/SDL.h>
#include <chrono>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <imgui_impl_sdlrenderer.h>
#include <iostream>
#include <map>
#include <memory>
#include <ratio>
#include <sstream>
#include <stb_image.h>
#include <string>
#include <thread>

using namespace Hallucen;

struct EngineData {

  SDL_Window *window = nullptr;
  SDL_GLContext context;
  bool initialised = false;
  bool windowOpen = false;

  Vector2i size;
  Vector2i frameBuffersize;
  std::shared_ptr<Scene> Hscene;
  std::map<SDL_Keycode, bool> keyboard;
  SDL_Renderer *sdlrenderer;
};

struct vkData {

  VkPhysicalDevice gpu;
  VkInstance instance;
  VkDevice device;
  VkSurfaceKHR presentation_surface;
  VkQueue graphics_queue;
  VkSwapchainKHR swap_chain = NULL;

  unsigned int graphicsQueueindex;
  VkDebugReportCallbackEXT debugCallback;
  std::vector<std::string> found_layers;
  std::vector<std::string> found_extensions;
  std::vector<VkImage> chain_images;
};

static EngineData data;
static vkData vkData;

bool Engine::init() {

  data.initialised = true;
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {

    std::cout << "Failed to initialise SDL\n";
    data.initialised = false;
    return false;
  }
  // SDL_GL_LoadLibrary(NULL);
  data.initialised = true;

  return true;
}

bool Engine::initVulkan() {

  vkData.found_extensions = VK::getAvailableVulkanExtensions(data.window);

  vkData.found_layers = VK::getAvailableVulkanLayers();

  if (vkData.found_layers.size() != VK::getRequestedLayerNames().size()) {
    std::cout << "warning! not all layers found\n";
  }

  vkData.instance =
      VK::createInstance(vkData.found_layers, vkData.found_extensions);

  vkData.debugCallback = VK::setupDebugCallback(vkData.instance);

  vkData.graphicsQueueindex = -1;
  vkData.gpu = VK::selectGPU(vkData.graphicsQueueindex, vkData.instance);

  if (!VK::createLogicalDevice(vkData.gpu, vkData.graphicsQueueindex,
                               vkData.found_layers, vkData.device))
    return false;

  if (!VK::createSurface(data.window, vkData.instance, vkData.gpu,
                         vkData.graphicsQueueindex,
                         vkData.presentation_surface))
    return false;
  if (!VK::createSwapChain(vkData.presentation_surface, vkData.gpu,
                           vkData.device, vkData.swap_chain))
    return false;

  if (!VK::getSwapChainImageHandles(vkData.device, vkData.swap_chain,
                                    vkData.chain_images))
    return false;
  VK::getDeviceQueue(vkData.device, vkData.graphicsQueueindex,
                     vkData.graphics_queue);

  return true;
}
bool Engine::initWindow(int width, int height, const std::string &name) {
  if (!data.initialised) {
    std::cout << "SDL has not been initialised\n";
    return false;
  }

  data.window = SDL_CreateWindow(name.c_str(), 0, 0, width, height,
                                 SDL_WINDOW_VULKAN | SDL_WINDOW_SHOWN);

  if (data.window == nullptr) {
    std::cout << "Failed to initialise window";
    return false;
  }

  data.size = {width, height};

  initVulkan();
  data.sdlrenderer =
      SDL_CreateRenderer(data.window, 0, SDL_RENDERER_ACCELERATED);
  stbi_set_flip_vertically_on_load(1);
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  ImGui::StyleColorsDark();

  // ImGui_ImplSDL2_InitForOpenGL(Engine::getWindow(), true);
  // ImGui_ImplSDL2_InitForOpenGL(data.window, data.context);
  ImGui_ImplSDL2_InitForSDLRenderer(data.window, data.sdlrenderer);
  ImGui_ImplSDLRenderer_Init(data.sdlrenderer);
  GL::Renderer::init();

  return true;
}

void Engine::Update(float deltaTime) {}

bool Engine::isKeyDown(SDL_Keycode key) { return data.keyboard[key]; }

void Engine::mainLoop() {}

void Engine::cleanup() {

  if (!data.initialised) {
    std::cout << "Hallucen was not initialised,nothing to clean up\n";
    return;
  }
  GL::Renderer::shutDown();

  // glfwDestroyWindow(data.window);
  SDL_DestroyWindow(data.window);
  vkDestroySwapchainKHR(vkData.device, vkData.swap_chain, nullptr);
  vkDestroyDevice(vkData.device, nullptr);
  vkDestroyDebugReportCallbackEXT(vkData.instance, vkData.debugCallback,
                                  nullptr);
  vkDestroySurfaceKHR(vkData.instance, vkData.presentation_surface, nullptr);
  vkDestroyInstance(vkData.instance, nullptr);
  SDL_Quit();
  SDL_Vulkan_UnloadLibrary();
  SDL_Quit();
}

std::string Engine::loadFile(const std::string &path) {
  std::ifstream t(path);
  std::stringstream buffer;
  buffer << t.rdbuf();
  return buffer.str();
}

SDL_Window *Engine::getWindow() { return data.window; }

std::shared_ptr<Image> Engine::loadImage(const std::string &path) {
  int width, height, nrChannels;
  unsigned char *data =
      stbi_load(path.c_str(), &width, &height, &nrChannels, 4);

  std::shared_ptr<Image> imageptr = Hallucen::make_Ref<Image>();
  imageptr->width = width;
  imageptr->height = height;
  imageptr->nrchannels = nrChannels;
  imageptr->data = data;

  return imageptr;
}

Vector2i Engine::getSize() {

  //  glfwGetFramebufferSize(window, &size.x, &size.y);
  SDL_GetWindowSize(data.window, &data.size.x, &data.size.y);

  return data.size;
}
Vector2i Engine::getFrameBufferSize() {

  //  glfwGetFramebufferSize(window, &size.x, &size.y);
  SDL_GL_GetDrawableSize(data.window, &data.frameBuffersize.x,
                         &data.frameBuffersize.y);

  return data.frameBuffersize;
}

void Engine::runScene(std::shared_ptr<Scene> scene) {
  ProfileFunc;
  float totalframetime;
  data.Hscene = scene;

  data.windowOpen = true;
  while (data.windowOpen) {
    Stopwatch watch;
    // GL::Renderer::clear({0.0f, 0.0f, 0.0f});
    SDL_RenderClear(data.sdlrenderer);

    // ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame(data.window);
    // ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    scene->ImGuiLogic(totalframetime);
    scene->render();
    ImGui::Render();

    // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

    SDL_RenderPresent(data.sdlrenderer);
    // SDL_GL_SwapWindow(data.window);

    // glfwPollEvents();
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT) {
        data.windowOpen = false;
      } else if (event.type == SDL_KEYDOWN) {
        data.keyboard[event.key.keysym.sym] = true;

        scene->handleKey(event.key.keysym.sym); // TODO refactor and delete
      } else if (event.type == SDL_KEYUP) {
        data.keyboard[event.key.keysym.sym] = false;
      } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        scene->onMouseDown();
      }
    }
    Update(watch.getTimeMs());
    scene->update(watch.getTimeMs());
    totalframetime = watch.getTimeMs();

    if (totalframetime < 8.0f) {
      ZoneScopedN("sleeping");
      int frametimenano = totalframetime * 1000000;
      std::chrono::nanoseconds secs(8000000 - frametimenano);
      std::this_thread::sleep_for(secs);
    }
    FrameMark;
  }
}

void Engine::frameBufferSizeCallback(GLFWwindow *win, int width, int height) {
  data.size.x = width;
  data.size.y = height;
  glViewport(0, 0, width, height);

  // TODO fix weird resizing problem
  // data.Hscene->winSizeChanged(data.size);
}

glm::vec2 Engine::getMousePosition() {
  int x, y;
  SDL_GetMouseState(&x, &y);
  y = data.size.y - y;
  return glm::vec2(x, y);
}

glm::vec2 Engine::getMousePositionRelative(GL::Camera2D &cam) {
  int x, y;
  SDL_GetMouseState(&x, &y);
  y = data.size.y - y;

  y += cam.getPosition().y;
  x += cam.getPosition().x;
  return glm::vec2(x, y);
}