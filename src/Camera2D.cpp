#include "Hallucen/GL/Camera2D.h"
#include "Hallucen/Hallucen.h"
#include "ext/matrix_clip_space.hpp"
#include "fwd.hpp"
#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace Hallucen;
using namespace Hallucen::GL;

Camera2D::Camera2D(float width, float height) {
  m_Pos = {0.0f, 0.0f};
  m_Size = {width, height};
  m_View = glm::translate(glm::mat4(1.0f), -glm::vec3(m_Pos.x, m_Pos.y, 0.0f));
  m_Proj = glm::ortho(0.0f, width, 0.0f, height);

  m_ViewProj = m_Proj * m_View;

}
Camera2D::Camera2D(Vector2 size) {

  m_Pos = {0.0f, 0.0f};
  m_Size = size;
  m_View = glm::translate(glm::mat4(1.0f), -glm::vec3(0.0f, 0.0f, 0.0f));
  m_Proj = glm::ortho(0.0f, size.x, 0.0f, size.y);

  m_ViewProj = m_Proj * m_View;
}
Camera2D::Camera2D(float width, float height, float x, float y) {
  m_Pos = {x, y};
  m_Size = {width, height};
  m_View = glm::translate(glm::mat4(1.0f), -glm::vec3(m_Pos.x, m_Pos.y, 0.0f));
  m_Proj = glm::ortho(0.0f, width, 0.0f, height);

  m_ViewProj = m_Proj * m_View;
}
Camera2D::Camera2D(Vector2 size, Vector2 position) {
  m_Pos = position;
  m_Size = size;
  m_View = glm::translate(glm::mat4(1.0f), -glm::vec3(m_Pos.x, m_Pos.y, 0.0f));
  m_Proj = glm::ortho(0.0f, m_Size.x, 0.0f, m_Size.y);

  m_ViewProj = m_Proj * m_View;
}

void Camera2D::updateMatrix() {
  m_View = glm::translate(glm::mat4(1.0f), -glm::vec3(m_Pos.x, m_Pos.y, 0.0f));
  m_Proj = glm::ortho(0.0f, m_Size.x, 0.0f, m_Size.y);

  m_ViewProj = m_Proj * m_View;
}

