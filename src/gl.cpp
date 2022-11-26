#include "Hallucen/GL/gl.h"

void Hallucen::GL::activateTextureUnit(unsigned int index) {
  glActiveTexture(GL_TEXTURE0 + index);

}