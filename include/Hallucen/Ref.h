#pragma once

#include <memory>

#include "tracy/Tracy.hpp"
namespace Hallucen {

// template <typename T> class Ref : public std::shared_ptr<T> {
// public:
//   Ref<T>() { std::shared_ptr<T>(); }
//   Ref<T>(std::shared_ptr<T> &&other) : std::shared_ptr<T>(other) {}

//   ~Ref<T>() {}
// };

template <typename T> struct Deleter {
  void operator()(T *p) { TracyFree(p); }
};

template <typename T> using Ref = std::shared_ptr<T>;

template <typename T, typename... Args> Ref<T> make_Ref(Args &&...args) {



#ifdef DEBUG

  Ref<T> ptr(new T(std::forward<Args>(args)...), Deleter<T>());
#else

  Ref<T> ptr = std::make_shared<T>(std::forward<Args>(args)...);

#endif

  TracyAlloc(ptr.get(), sizeof(T));

  return ptr;
}
} // namespace Hallucen