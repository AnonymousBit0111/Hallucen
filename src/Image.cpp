#include "Hallucen/Image.h"
#include "stb_image.h"

Hallucen::Image::~Image(){


    stbi_image_free(data);
}