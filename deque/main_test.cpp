#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() function

#include <algorithm>
#include <catch.hpp>
#include <vector>

#include "deque.hpp"
#include "dequeList.hpp"

using namespace std;

// Test case for DequeList::is_empty
TEST_CASE("DequeList<T>::is_empty()", "[DequeList]") {
  DequeList<int> d1(5);
  REQUIRE(d1.is_empty() == true);

  d1.append_left(5);
  REQUIRE(d1.is_empty() == false);
}

TEST_CASE("DequeList::operator=", "[DequeList]") {
  DequeList<int> d1(4);
  vector v1{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120};
  for (auto& e : v1) {
    d1.append_left(e);
  }

  DequeList<int> d2(4);
  d2 = d1;

  auto r1 = d1.print();
  auto r2 = d2.print();
  REQUIRE(r1 == r2);
}

TEST_CASE("DequeList<T>::append_left()", "[DequeList]") {
  // testing append left on an empty deque
  {
    DequeList<int> dl(3);
    vector<int> v{100};
    for (auto& e : v) {
      dl.append_left(e);
    }
    vector<int> resdl = dl.print();
    REQUIRE(resdl == v);
    REQUIRE(dl.get_count() == (int)v.size());
  }
  // testing append left to see if it appends to the prior block when necessary
  {
    DequeList<int> dl(3);
    vector<int> v{100, 99, 98};
    int capBefore = dl.get_capacity();
    for (auto& e : v) {
      dl.append_left(e);
    }
    vector<int> resdl = dl.print();
    reverse(resdl.begin(), resdl.end());
    REQUIRE(resdl == v);
    REQUIRE(dl.get_count() == (int)v.size());
    REQUIRE(capBefore == dl.get_capacity());

    DequeList<int>::DLInternalState expected = {
        4,  // map_size
        3,  // block_size
        3,  // count
        1,  // start_block
        2,  // end_block
        1,  // front_index
        0   // back_index
    };
    DequeList<int>::DLInternalState result;
    dl.get_internal_state(result);
    REQUIRE(expected == result);
  }

  // testing append left to see if deque can expand itself when necessary
}

// Test case for DequeList::append_right
TEST_CASE("DequeList<T>::append_right()", "[DequeList]") {
  // testing append right on an empty deque; adding 2 elements no block
  // expansion
  DequeList<int> d1(3);
  vector<int> v1{10, 20};
  for (auto& e : v1) {
    d1.append_right(e);
  }
  vector<int> resd1 = d1.print();
  REQUIRE(resd1 == v1);
  REQUIRE(d1.get_count() == (int)v1.size());

  // testing append right to see if the deque appends to the next block when
  // initial block is full
  DequeList<int> d2(3);
  vector<int> v2{10, 20, 30, 40};
  for (auto& e : v2) {
    d2.append_right(e);
  }
  vector<int> resd2 = d2.print();
  REQUIRE(resd2 == v2);
  REQUIRE(d2.get_count() == (int)v2.size());

  // testing append right to see if the deque properly expands itself when
  // necessary
  DequeList<int> d3(3);
  vector<int> v3{10, 20, 30, 40, 50, 60, 70, 80, 90};
  for (auto& e : v3) {
    d3.append_right(e);
  }
  vector<int> resd3 = d3.print();
  REQUIRE(resd3 == v3);
  REQUIRE(d3.get_count() == (int)v3.size());
}

TEST_CASE("DequeList<T>:pop_left()", "[DequeList]") {
  // popping an empty Deque
  DequeList<int> d1(5);
  REQUIRE_THROWS_AS(d1.pop_left(), runtime_error);

  // pop left on a full deque appended from right
  for (int i = 1; i < 11; i++) {
    d1.append_right(i);
  }
  // pop left 3 times to check functionality
  for (int i = 0; i < 3; i++) {
    d1.pop_left();
  }

  vector<int> res{4, 5, 6, 7, 8, 9, 10};
  vector<int> resu = d1.print();
  REQUIRE(resu == res);
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

TEST_CASE("DequeList<T>::pop_right() till empty", "[DequeList]") {
  DequeList<int> d1(5);
  for (int i = 1; i <= 10; i++) {
    d1.append_right(i);
  }
  for (int i = 1; i <= 10; i++) {
    d1.pop_right();
  }

  REQUIRE(d1.is_empty() == true);
}

TEST_CASE("DequeList<T>::append_left_after_pop()", "[DequeList]") {
  // testing the edge case where we append then pop a deque till it has
  //  1 element remaining. Then try to append_left again
  DequeList<int> d1(4);
  for (int i = 1; i < 10; i++) {
    d1.append_left(i);
  }
  // pop right so that deque will look like {9,-,-,-}{-,-,-,-}{-,-,-,-}
  // internally
  for (int i = 1; i < 9; i++) {
    d1.pop_right();
  }

  d1.append_left(2);
  vector<int> res{2, 9};
  vector<int> v = d1.print();
  REQUIRE(v == res);

  DequeList<int>::DLInternalState expected = {
      4,  // map_size
      4,  // block_size
      1,  // count
      0,  // start_block
      0,  // end_block
      0,  // front_index
      0   // back_index
  };
  /* DequeList<int>::DLInternalState result;
  d1.get_internal_state(result);
  REQUIRE(expected == result); */
}

TEST_CASE("DequeList<T>::append_right_after_pop", "[DequeList]") {
  // testing the edge case where we append then pop a deque till it has
  //  1 element remaining. Then try to append_right again
  DequeList<int> d1(4);
  for (int i = 1; i < 11; i++) {
    d1.append_right(i);
  }
  // pop right so that deque will look like {9,-,-,-}{-,-,-,-}{-,-,-,-}
  // internally
  for (int i = 1; i < 10; i++) {
    d1.pop_left();
  }
  d1.append_right(11);
  vector<int> res{10, 11};
  vector<int> v = d1.print();
  REQUIRE(v == res);
}

TEST_CASE("DequeList<T>::append_left_bug()", "[DequeList]") {
  // testing append right on an empty deque; adding 2 elements no block
  // expansion
  DequeList<int> d1(3);
  vector<int> v1{90, 80, 70, 60, 50, 40, 30, 20, 10};
  for (auto& e : v1) {
    d1.append_left(e);
  }
  vector<int> resd1 = d1.print();
  vector<int> exp = {10, 20, 30, 40, 50, 60, 70, 80, 90};
  REQUIRE(resd1 == exp);
  REQUIRE(d1.get_count() == (int)v1.size());
}

TEST_CASE("DequeList<T>::peek_left()", "[DequeList]") {
  DequeList<int> d1(3);
  vector<int> v1{10, 20, 30, 40};
  for (auto& e : v1) {
    d1.append_left(e);
  }
  int front = d1.peek_left();
  int expected = 40;
  REQUIRE(front == expected);
}

TEST_CASE("DequeList<T>::peek_right()", "[DequeList]") {
  DequeList<int> d1(3);
  vector<int> v1{10, 20, 30, 40};
  for (auto& e : v1) {
    d1.append_left(e);
  }
  int front = d1.peek_right();
  int expected = 10;
  REQUIRE(front == expected);
}

TEST_CASE("DequeList<T>::at()", "[DequeList]") {
  DequeList<int> d1(3);
  vector<int> v1{10, 20, 30, 40};
  for (auto& e : v1) {
    d1.append_left(e);
  }
  int first = d1.at(0);
  int third = d1.at(2);
  REQUIRE(first == 40);
  REQUIRE(third == 20);
}
