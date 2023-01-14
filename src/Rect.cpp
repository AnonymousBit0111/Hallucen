

#include "Hallucen/Rect.h"
#include "Hallucen/vector.h"

using namespace Hallucen;
using namespace Hallucen::GL;

void Rect::updateVerts() {
  vertices = {
      Vertex{
          m_Position.x,
          m_Position.y,
          m_Colour.x,
          m_Colour.y,
          m_Colour.z,

      },
      // top left
      Vertex{
          m_Position.x + m_Size.x,
          m_Position.y,

          m_Colour.x,

          m_Colour.y,

          m_Colour.z,

      },
      // top right
      Vertex{
          m_Position.x + m_Size.x,
          m_Position.y - m_Size.y,

          m_Colour.x,

          m_Colour.y,

          m_Colour.z,

      },
      // bottom right
      Vertex{
          m_Position.x,
          m_Position.y - m_Size.y,
          m_Colour.x,

          m_Colour.y,

          m_Colour.z,

      },
      // bottom left
  };
}
Rect::Rect(Vector2 size, Vector2 position, Vector3 colour)
    : m_Size(size), m_Position(position), m_Colour(colour) {
  vertices = {
      Vertex{
          m_Position.x,
          m_Position.y,
          m_Colour.x,
          m_Colour.y,
          m_Colour.z,

      },
      // top left
      Vertex{
          m_Position.x + m_Size.x,
          m_Position.y,

          m_Colour.x,

          m_Colour.y,

          m_Colour.z,

      },
      // top right
      Vertex{
          m_Position.x + m_Size.x,
          m_Position.y - m_Size.y,

          m_Colour.x,

          m_Colour.y,

          m_Colour.z,

      },
      // bottom right
      Vertex{
          m_Position.x,
          m_Position.y - m_Size.y,
          m_Colour.x,

          m_Colour.y,

          m_Colour.z,

      },
      // bottom left
  };
}

void Rect::setColour(Vector3 rgb) {
  for (auto &i : vertices) {
    i.r = rgb.x;
    i.g = rgb.y;
    i.b = rgb.z;
  }
}

bool Rect::contains(Vector2 pos) {
  bool a = (pos.x > vertices[0].x);
  bool b = (pos.x < vertices[1].x);
  bool c = (pos.y > vertices[0].y);
  bool d = (pos.y < vertices[3].y);

  return (a && b && c && d);
}

void Rect::move(glm::vec2 pos) {
  for (auto &i : vertices) {
    i.x += pos.x;
    i.y += pos.y;
  }
}

void Rect::setPosition(glm::vec2 pos) {
  this->m_Position = {pos.x, pos.y};
  updateVerts();
}