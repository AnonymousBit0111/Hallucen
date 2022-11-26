
#pragma once
#include <chrono>

class Stopwatch {
public:
  Stopwatch();
  float getTimeMs();
  ~Stopwatch();

private:
  std::chrono::time_point<std::chrono::steady_clock> startTime;
};