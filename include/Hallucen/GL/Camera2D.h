#pragma once
#include "Hallucen/vector.h"
#include "fwd.hpp"
#include <glm/glm.hpp>
namespace Hallucen {
namespace GL {

class Camera2D {

private:
  glm::mat4 m_View;
  glm::mat4 m_Proj;
  glm::mat4 m_ViewProj;
  Vector2 m_Size;
  Vector2 m_Pos;

  float m_zoomLevel =1;
  void updateMatrix();

public:
  Camera2D(float width, float height);
  Camera2D(Vector2 size);
  Camera2D(float width, float height, float x, float y);
  Camera2D(Vector2 size, Vector2 position);
  inline Vector2 getSize() { return m_Size; }
  inline void setSize(Vector2 size) {
    m_Size = size;
    updateMatrix();
  }
  inline void setPosition(Vector2 pos) {
    m_Pos = pos;
    updateMatrix();
  }

  void zoom(float level);
  void move(Vector2 pos);
  inline Vector2 getPosition() { return m_Pos; }
  inline glm::mat4 getViewMatrix() { return m_View; }
  inline glm::mat4 getProjMatrix() { return m_Proj; }
  inline glm::mat4 getViewProjMatrix() { return m_ViewProj; }

};
} // namespace GL
} // namespace Hallucen