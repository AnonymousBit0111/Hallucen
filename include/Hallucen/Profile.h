#pragma once
#include "tracy/Tracy.hpp"

#define ProfileFunc                                                            \
  TracyFunction;                                                               \
  ZoneScoped;