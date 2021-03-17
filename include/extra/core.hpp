#pragma once

#include <type_traits>

namespace extra {

template <typename T>
requires std::is_rvalue_reference_v<T&&>
std::remove_reference_t<T>& lvalue_cast(T&& x) {
  return x;
}

template <typename>
struct dependent_false : std::false_type {};

}  // namespace extra
