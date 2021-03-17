#include <atomic>
#include <ranges>
#include <vector>

#include <boost/test/unit_test.hpp>

#include "extra/fix_vector.hpp"

using extra::fix_vector;

BOOST_AUTO_TEST_CASE(fix_vector_test) {
  BOOST_TEST(std::ranges::range<fix_vector<int>>);
  BOOST_TEST(std::ranges::sized_range<fix_vector<int>>);
  BOOST_TEST(std::ranges::random_access_range<fix_vector<int>>);
  BOOST_TEST(std::ranges::contiguous_range<fix_vector<int>>);
  BOOST_TEST(std::ranges::common_range<fix_vector<int>>);

  fix_vector<int> b0(100);
  fix_vector<int> b1(b0);
  fix_vector<int> b2(std::move(b0));
  b1 = b2;

  fix_vector<int> b3;
  BOOST_TEST(b3.empty());
  BOOST_TEST(b3.size() == 0);

  fix_vector<int> b4(10, 1);

  std::vector<int> v;

  fix_vector<int> b5(v);
  fix_vector<int> b6(v.begin(), v.end());
  fix_vector<int> b7{31, 32};
  BOOST_TEST(b7.size() = 2);

  fix_vector<std::atomic<int>> c0(100);
  fix_vector<std::atomic<int>> c1(100, 2);
  fix_vector<std::atomic<int>> c2(v);
  fix_vector<std::atomic<int>> c3{0, 1, 2, 3};
  BOOST_TEST(c3.size() == 4);
}
