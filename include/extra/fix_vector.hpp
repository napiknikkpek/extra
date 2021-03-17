#pragma once

#include <concepts>
#include <memory>
#include <ranges>

#include <boost/stl_interfaces/sequence_container_interface.hpp>

namespace extra {

template <typename T>
class fix_vector
    : public boost::stl_interfaces::sequence_container_interface<
          fix_vector<T>, boost::stl_interfaces::element_layout::contiguous> {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = T const&;
  using iterator = T*;
  using const_iterator = T const*;
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;

 private:
  std::unique_ptr<T[]> storage;
  size_type total = 0;

 public:
  fix_vector() = default;

  fix_vector(fix_vector const& a) : fix_vector(a.size()) {
    std::ranges::copy(a, begin());
  }

  fix_vector(fix_vector&& a) noexcept { swap(a); }

  explicit fix_vector(size_type s)
      : storage(std::make_unique<T[]>(s)), total(s) {}

  template<typename X>
  requires std::constructible_from<T, X>
  explicit fix_vector(size_type s, X const& val): fix_vector(s) {
    std::ranges::fill(*this, val);
  }

  template <std::random_access_iterator Iter>
  fix_vector(Iter first, Iter last) : fix_vector(std::distance(first, last)) {
    std::ranges::copy(first, last, begin());
  }

  fix_vector(std::ranges::sized_range auto const& r) : fix_vector(r.size()) {
    std::ranges::copy(r, begin());
  }

  template<typename X>
  requires std::constructible_from<T, X>
  fix_vector(std::initializer_list<X> init) : fix_vector(init.size()) {
    std::ranges::copy(init, begin());
  }

  fix_vector<T>& operator=(fix_vector const& a) {
    if (total != a.size()) {
      storage = std::make_unique<T[]>(a.size());
      total = a.size();
    }
    std::ranges::copy(a, begin());
    return *this;
  }

  fix_vector<T>& operator=(fix_vector<T>&& a) noexcept {
    swap(a);
    return *this;
  }

  void swap(fix_vector<T>& a) noexcept {
    std::swap(storage, a.storage);
    std::swap(total, a.total);
  }

  iterator begin() noexcept { return storage.get(); }
  iterator end() noexcept { return storage.get() + total; }

  size_type max_size() const noexcept {
    return std::numeric_limits<difference_type>::max();
  }

  using base = boost::stl_interfaces::sequence_container_interface<
      fix_vector<T>, boost::stl_interfaces::element_layout::contiguous>;
  using base::begin;
  using base::end;
};

}  // namespace extra
