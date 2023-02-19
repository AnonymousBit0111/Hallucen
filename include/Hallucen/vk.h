

#pragma once

#include "vulkan/vulkan_core.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <vulkan/vulkan.hpp>

namespace VK {
static VkPresentModeKHR gPresentationMode = VK_PRESENT_MODE_FIFO_RELAXED_KHR;
static VkSurfaceTransformFlagBitsKHR gTransform =
    VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
static VkFormat gFormat = VK_FORMAT_B8G8R8A8_SRGB;
static VkColorSpaceKHR gColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
static VkImageUsageFlags gImageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

std::vector<std::string> getAvailableVulkanExtensions(SDL_Window *window);
std::vector<std::string> getAvailableVulkanLayers();
const std::set<std::string> &getRequestedLayerNames();
inline const std::set<std::string> &getRequestedDeviceExtensionNames() {
  static std::set<std::string> layers;
  if (layers.empty()) {
    layers.emplace(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
  }
  return layers;
}
inline const std::vector<VkImageUsageFlags> getRequestedImageUsages() {
  static std::vector<VkImageUsageFlags> usages;
  if (usages.empty()) {
    usages.emplace_back(VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT);
  }
  return usages;
}
inline void getDeviceQueue(VkDevice device, int familyQueueIndex,
                           VkQueue &outGraphicsQueue) {
  vkGetDeviceQueue(device, familyQueueIndex, 0, &outGraphicsQueue);
}

VkInstance createInstance(std::vector<std::string> layers,
                          std::vector<std::string> extensions);
VkResult createDebugReportCallbackEXT(
    VkInstance instance, const VkDebugReportCallbackCreateInfoEXT *pCreateInfo,
    const VkAllocationCallbacks *pAllocator,
    VkDebugReportCallbackEXT *pCallback);
VkDebugReportCallbackEXT setupDebugCallback(VkInstance &instance);
VkPhysicalDevice selectGPU(unsigned int &graphicsQueueindex,
                           VkInstance instance);

bool createLogicalDevice(VkPhysicalDevice &physicalDevice,
                         unsigned int queueFamilyIndex,
                         const std::vector<std::string> &layerNames,
                         VkDevice &outDevice);
bool createSurface(SDL_Window *window, VkInstance instance,
                   VkPhysicalDevice gpu, uint32_t graphicsFamilyQueueIndex,
                   VkSurfaceKHR &outSurface);
bool getPresentationMode(VkSurfaceKHR surface, VkPhysicalDevice device,
                         VkPresentModeKHR &ioMode);
bool getSurfaceProperties(VkPhysicalDevice device, VkSurfaceKHR surface,
                          VkSurfaceCapabilitiesKHR &capabilities);
inline unsigned int
getNumberOfSwapImages(const VkSurfaceCapabilitiesKHR &capabilities) {
  unsigned int number = capabilities.minImageCount + 1;
  return number > capabilities.maxImageCount ? capabilities.minImageCount
                                             : number;
}

VkExtent2D getSwapImageSize(const VkSurfaceCapabilitiesKHR &capabilities);

bool getImageUsage(const VkSurfaceCapabilitiesKHR &capabilities,
                   VkImageUsageFlags &outUsage);

inline VkSurfaceTransformFlagBitsKHR
getTransform(const VkSurfaceCapabilitiesKHR &capabilities) {
  if (capabilities.supportedTransforms & gTransform)
    return gTransform;
  std::cout << "unsupported surface transform: " << gTransform;
  return capabilities.currentTransform;
}
bool getFormat(VkPhysicalDevice device, VkSurfaceKHR surface,
               VkSurfaceFormatKHR &outFormat);
bool createSwapChain(VkSurfaceKHR surface, VkPhysicalDevice physicalDevice,
                     VkDevice device, VkSwapchainKHR &outSwapChain);
bool getSwapChainImageHandles(VkDevice device, VkSwapchainKHR chain,
                              std::vector<VkImage> &outImageHandles);

} // namespace VK
