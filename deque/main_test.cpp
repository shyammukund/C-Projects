#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() function

#include <catch.hpp>
#include <vector>

#include "deque.hpp"
#include "dequeList.hpp"

using namespace std;

// Test case for DequeList::append_right
TEST_CASE("DequeList<T>::append_right()", "[DequeList]") {
  // testing append: on an empty deque; adding 2 elements no block expansion
  DequeList<int> d1(3);
  vector<int> v2{10, 20};
  for (auto& e : v2) {
    d1.append_right(e);
  }
  vector<int> res = d1.print();
  REQUIRE(res == v2);
  REQUIRE(d1.get_count() == (int)v2.size());
  //
}

// Test case for DequeList::is_empty
TEST_CASE("DequeList<T>::is_empty()", "[DequeList]") {
  DequeList<int> d1(5);
  REQUIRE(d1.is_empty() == true);

  d1.append_left(5);
  REQUIRE(d1.is_empty() == false);
}

// Test case for DequeList::pop_left throwing an exception
TEST_CASE("DequeList<T>::pop_left() throws on empty DequeList", "[DequeList]") {
  DequeList<int> d1(5);

  // Ensure the deque is empty
  REQUIRE(d1.is_empty() == true);

  // Test that pop_left() throws an exception when the deque is empty
  REQUIRE_THROWS_AS(d1.pop_left(), std::runtime_error);
}

// Test case for DequeList::pop_right throwing an exception
TEST_CASE("DequeList<T>::pop_right() throws on empty DequeList",
          "[DequeList]") {
  DequeList<int> d1(5);

  // Ensure the deque is empty
  REQUIRE(d1.is_empty() == true);

  // Test that pop_right() throws an exception when the deque is empty
  REQUIRE_THROWS_AS(d1.pop_right(), std::runtime_error);
}

// Test case for Deque::push_front and Deque::pop_front
TEST_CASE("Deque<T>::append_left() and pop_front()", "[Deque]") {
  Deque<int> d1(5);

  d1.append_left(10);
  d1.append_left(20);
  d1.append_left(30);

  REQUIRE(d1.pop_left() == 30);
  REQUIRE(d1.pop_left() == 20);
  REQUIRE(d1.pop_left() == 10);
}