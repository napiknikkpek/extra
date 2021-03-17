#pragma once

#include <functional>
#include <iterator>

#include <boost/stl_interfaces/iterator_interface.hpp>

namespace extra {

template <typename F>
struct function_output_iterator
    : boost::stl_interfaces::iterator_interface<function_output_iterator<F>,
                                                std::output_iterator_tag, int,
                                                function_output_iterator<F>&> {
  F* f = nullptr;

  function_output_iterator() = default;
  function_output_iterator(F* f) : f{f} {}

  template <typename T>
  function_output_iterator& operator=(T&& t) {
    std::invoke(*f, std::forward<T>(t));
    return *this;
  }

  function_output_iterator& operator*() { return *this; }
  function_output_iterator& operator++() { return *this; }

  using base_type =
      boost::stl_interfaces::iterator_interface<function_output_iterator<F>,
                                                std::output_iterator_tag, int,
                                                function_output_iterator<F>&>;
  using base_type::operator++;
};

template <typename F>
function_output_iterator(F*) -> function_output_iterator<F>;

}  // namespace extra
