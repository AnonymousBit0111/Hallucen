#pragma once

#include <memory>

#include "tracy/Tracy.hpp"
namespace Hallucen {

template <typename T> class Ref : public std::shared_ptr<T> {
public:
  Ref<T>() { std::shared_ptr<T>(); }
  Ref<T>(std::shared_ptr<T> &&other) : std::shared_ptr<T>(other) {}
  ~Ref<T>() {}
};
template <typename T, class... Args> Ref<T> make_Ref(Args &&...args) {

  Ref<T> a = std::make_shared<T>(std::forward<Args>(args)...);

  TracyAlloc(a.get(), sizeof(T));

  return a;
}
} // namespace Hallucen