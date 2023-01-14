#include "Hallucen/TexRect.h"
#include "Hallucen/vector.h"
#include "fwd.hpp"
#include <cassert>
#include <vector>
using namespace Hallucen;
using namespace GL;

void TexRect::updateVerts() {
  vertices = {
      TextureVertex{m_Position.x, m_Position.y, m_Colour.x, m_Colour.y,
                    m_Colour.z, vertices[0].tx, vertices[0].ty

      },
      // top left
      TextureVertex{m_Position.x + m_Size.x, m_Position.y,

                    m_Colour.x,

                    m_Colour.y,

                    m_Colour.z, m_Size.x, 0

      },
      // top right
      TextureVertex{m_Position.x + m_Size.x, m_Position.y - m_Size.y,

                    m_Colour.x,

                    m_Colour.y,

                    m_Colour.z, m_Size.x, m_Size.y

      },
      // bottom  right
      TextureVertex{m_Position.x, m_Position.y - m_Size.y, m_Colour.x,

                    m_Colour.y,

                    m_Colour.z, 0, m_Size.y

      },
      // bottom left
  };
}

TexRect::TexRect(Vector2 size, Vector2 position, Vector3 colour)
    : m_Size(size), m_Position(position) {
  m_Colour.x = colour.x;
  m_Colour.y = colour.y;
  m_Colour.z = colour.z;
  vertices = {
      TextureVertex{m_Position.x, m_Position.y, colour.x, colour.y, colour.z, 0,
                    0

      },
      // top left
      TextureVertex{m_Position.x + size.x, m_Position.y,

                    colour.x,

                    colour.y,

                    colour.z, m_Size.x, 0

      },
      // top right
      TextureVertex{m_Position.x + size.x, m_Position.y - m_Size.y,

                    colour.x,

                    colour.y,

                    colour.z, m_Size.x, m_Size.y

      },
      // bottom right
      TextureVertex{m_Position.x, m_Position.y - size.y, colour.x,

                    colour.y,

                    colour.z, 0, m_Size.y

      },
      // bottom left
  };
}

bool TexRect::contains(Vector2 pos) {
  bool a = (pos.x > vertices[0].x);
  bool b = (pos.x < vertices[1].x);
  bool c = (pos.y > vertices[0].y);
  bool d = (pos.y < vertices[3].y);

  return (a && b && c && d);
}

void TexRect::setColour(Vector3 rgb) {
  m_Colour = {rgb.x, rgb.y, rgb.z};
  for (auto &i : vertices) {
    i.r = rgb.x;
    i.g = rgb.y;
    i.b = rgb.z;
  }
}

void TexRect::move(glm::vec2 pos) {
  for (auto &i : vertices) {
    i.x += pos.x;
    i.y += pos.y;
  }
}

void TexRect::setTexCoords(std::vector<glm::vec2> &coords) {
  if (coords.size() != 4)
    assert(false);
  for (int i = 0; i < 4; i++) {
    vertices[i].tx = coords[i].x;
    vertices[i].ty = coords[i].y;
  }
}

std::vector<glm::vec2> TexRect::getTexCoords() {
  std::vector<glm::vec2> coords;
  for (int i = 0; i < 4; i++) {
    coords.push_back({vertices[i].x, vertices[i].y});
  }
  return coords;
}

void TexRect::setPosition(glm::vec2 pos) {
  m_Position = {pos.x, pos.y};
  updateVerts();
}

void TexRect::setSize(glm::vec2 size) {
  m_Size = {size.x, size.y};

  updateVerts();
}