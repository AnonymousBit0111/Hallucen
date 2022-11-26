#pragma once
#include <memory>
namespace Hallucen {
struct Image {
  int width, height, nrchannels;
  unsigned char *data;
  ~Image();
};
} // namespace Hallucen