
#include "Hallucen/Rect.h"
#include "Hallucen/vector.h"

using namespace Hallucen;
using namespace Hallucen::GL;

Rect::Rect(Vector2 size, Vector2 position, Vector3 colour)
    : m_Size(size), m_Position(position), m_Colour(colour) {
  Vector2 halfsize = {m_Size.x / 2, m_Size.y / 2};

  vertices = {
      Vertex{
          m_Position.x - halfsize.x,
          m_Position.y - halfsize.y,
          colour.x,
          colour.y,
          colour.z,

      },
      // bottom left
      Vertex{
          m_Position.x + halfsize.x,
          m_Position.y - halfsize.y,

          colour.x,

          colour.y,

          colour.z,

      },
      // bottom right
      Vertex{
          m_Position.x + halfsize.x,
          m_Position.y + halfsize.y,

          colour.x,

          colour.y,

          colour.z,

      },
      // top right
      Vertex{
          m_Position.x - halfsize.x,
          m_Position.y + halfsize.y,
          colour.x,

          colour.y,

          colour.z,

      },
      // top left
  };
}

void Rect::setColour(Vector3 rgb) {

  m_Colour = rgb;
  for (auto &i : vertices) {
    i.colour[0] = rgb.x;
    i.colour[1] = rgb.y;
    i.colour[2] = rgb.z;
  }
}

bool Rect::contains(Vector2 pos) {
  bool a = (pos.x > vertices[0].positions[0]);
  bool b = (pos.x < vertices[1].positions[0]);
  bool c = (pos.y > vertices[0].positions[1]);
  bool d = (pos.y < vertices[3].positions[1]);

  return (a && b && c && d);
}

void Rect::setPosition(Vector2 pos) {
  Vector2 halfsize = {m_Size.x / 2, m_Size.y / 2};

  vertices = {
      Vertex{
          m_Position.x - halfsize.x,
          m_Position.y - halfsize.y,
          m_Colour.x,
          m_Colour.y,
          m_Colour.z,

      },
      // bottom left
      Vertex{
          m_Position.x + halfsize.x,
          m_Position.y - halfsize.y,

          m_Colour.x,

          m_Colour.y,

          m_Colour.z,

      },
      // bottom right
      Vertex{
          m_Position.x + halfsize.x,
          m_Position.y + halfsize.y,

          m_Colour.x,

          m_Colour.y,

          m_Colour.z,

      },
      // top right
      Vertex{
          m_Position.x - halfsize.x,
          m_Position.y + halfsize.y,
          m_Colour.x,

          m_Colour.y,

          m_Colour.z,

      },
      // top left
  };
}
