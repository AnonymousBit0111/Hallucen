#pragma once

namespace Hallucen::GL {

struct Vertex {
  float x, y;
  float r, g, b;
};
struct TextureVertex {
  float x, y;
  float r, g, b;
  float tx, ty;
};
} // namespace Hallucen::GL