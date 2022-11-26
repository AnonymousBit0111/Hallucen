#include "Hallucen/Stopwatch.h"
#include <chrono>
#include <ratio>

Stopwatch::Stopwatch() {
  startTime = std::chrono::steady_clock::now();
}

float Stopwatch::getTimeMs() {

  auto now = std::chrono::steady_clock::now();

  auto timePassed = now - startTime;

  return static_cast<float>(timePassed.count()) /1000000;
}

Stopwatch::~Stopwatch() {}