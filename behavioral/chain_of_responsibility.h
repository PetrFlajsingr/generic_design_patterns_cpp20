//
// Created by Petr on 15.09.2020.
//

#ifndef DESIGN_PATTERNS_CHAIN_OF_RESPONSIBILITY_H
#define DESIGN_PATTERNS_CHAIN_OF_RESPONSIBILITY_H

#include "../concepts.h"
#include <functional>
#include <optional>
#include <vector>

namespace pf {
template<typename T, typename... Args>
class chain_of_responsibility {
 public:
  template<typename F>
  void add_handler(invocable_returning<F, std::optional<T>, Args...> auto &&h) {
    handlers.emplace_back(std::forward<F>(h));
  }

  std::optional<T> operator()(Args &&... args) {
    return notify(std::forward<Args>(args)...);
  }

  std::optional<T> notify(Args &&... args) {
    for (const auto &h : handlers) {
      if (auto res = h(args...); res.has_value()) {
        return res.value();
      }
    }
    return std::nullopt;
  }

 private:
  std::vector<std::function<std::optional<T>(Args...)>> handlers;
};
}// namespace pf
#endif//DESIGN_PATTERNS_CHAIN_OF_RESPONSIBILITY_H
