//
// Created by Petr on 15.09.2020.
//

#ifndef DESIGN_PATTERNS_ABSTRACT_FACTORY_H
#define DESIGN_PATTERNS_ABSTRACT_FACTORY_H
#include "../concepts.h"
#include <exception>
#include <functional>
#include <memory>
#include <unordered_map>

namespace pf {
template<enum_type E, typename ResultType, typename... Args>
class abstract_factory {
 public:
  using value_type = ResultType;
  using constructor_map = std::unordered_map<E, std::function<value_type(Args...)>>;

  explicit abstract_factory(constructor_map &&constructors) : constructors(constructors) {}

  value_type create(E type, Args &&... args) {
    if (const auto iter = constructors.find(type); iter != constructors.end()) {
      return iter->second(std::forward<Args>(args)...);
    }
    throw std::invalid_argument("Invalid enum type in abstract_factory.");
  }

 private:
  constructor_map constructors;
};
}// namespace pf
#endif//DESIGN_PATTERNS_ABSTRACT_FACTORY_H
