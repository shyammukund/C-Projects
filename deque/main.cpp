#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "deque.hpp"
#include "dequeList.hpp"

using namespace std;

void test_int_append() {
  Deque<int> intDeqOne;
  for (int i = 1; i <= 5; i++) {
    intDeqOne.append_left(i);
    intDeqOne.append_right(i);
  }
  cout << "Expected: 5, 4, 3, 2, 1, 1, 2, 3, 4, 5" << endl;
  cout << "Result: ";
  intDeqOne.print();

  // constant
  Deque<int> intDeqTwo(2, 4);
  for (int i = 1; i <= 16; i++) {
    intDeqTwo.append_left(i);
    intDeqTwo.append_right(i);
  }
  cout << "Expected: 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, "
          "2, 3, 4, 5, 6 , 7, 8, 9, 10, 11, 12, 13, 14, 15, 16"
       << endl;
  cout << "left 1 right 32 count 32 capacity 32" << endl;
  cout << "Result: ";

  intDeqTwo.print();
}

void test_string_append() {
  // Deque with initial capcity 5 and a resizing factor of 3
  Deque<string> strDeq(5, 3);

  for (int i = 1; i <= 5; i++) {
    strDeq.append_left("test");
    strDeq.append_right("string");
  }
  cout
      << "Expected: test test test test test string string string string string"
      << endl;
  cout << "left 3 right 12 count 10 capacity 15" << endl;
  cout << "Result :";
  strDeq.print();
}

/* void test_peek_pop_empty(){
    // Test peek and pop operations on an empty deque
    Deque deq(0);
    deq.pop_left();
    deq.pop_right();
    deq.peek_left();
    deq.peek_right();
}
 */

/* void test_basic(){
    // Test basic functionality.
    Deque deq(5);
    deq.append_left(1);
    deq.append_right(2);
    deq.pop_left();
    deq.pop_right();
    deq.peek_left();
    deq.peek_right();
}

void test_queue(){
    // Test FIFO behavior
    Deque deq(10);
     deq.pop_left();

    deq.peek_left();

}

void test_stack(){
    // Test LIFO behavior
    Deque deq(10);
     deq.peek_right();
      deq.pop_right();
} */


void dl_append_left_test() {
  cout << "testing DequeList<T>::append_left() : START " << endl;
  DequeList<int> d1(4);
  // add into empty DequeList
  d1.append_left(81);
  d1.print();

  // append to left after first insertion.
  // first insertion of a new block on the left
  d1.append_left(27);
  d1.print();
  d1.append_left(9);
  d1.print();
  d1.append_left(3);
  d1.print();

  // append left till a new block has to be created
  for (int i = 2; i > 0; i--) {
    d1.append_left(i);
  }
  d1.print();
}

void dl_test_append_right() {
  DequeList<int> d(4);
  cout << "testing DequeList<T>::append_left() : START " << endl;
  // insert empty on right
  d.append_right(1);
  d.print();

  // append right till have to move to next block
  for (int i = 2; i <= 5; i++) {
    d.append_right(i);
    d.print();
  }

  // append right till have to create a new block
  for (int j = 6; j <= 10; j++) {
    d.append_right(j);
  }
  d.print();
}

void dl_test_is_empty() {
  cout << "testing DequeList<T>::is_full() : START " << endl;
  DequeList<int> d1(5);
  bool result = d1.is_empty();
  assert(result == true);
  d1.append_left(5);
  result = d1.is_empty();
  assert(result == false);
  cout << "testing DequeList<T>::is_full() : PASSED " << endl;
}

void dl_test_is_full() {
  cout << "testing DequeList<T>::is_full() : START " << endl;
  DequeList<string> d1(2);
  assert(d1.is_full() == false);
  d1.append_left("Hello");
  assert(d1.is_full() == false);
  d1.append_right("World");
  assert(d1.is_full() == true);
  cout << "testing DequeList<T>::is_full() : PASSED " << endl;
}

int main(int, char**) {
  // test_int_append();
  // test_string_append();
  // dl_append_left_test();
  dl_test_append_right();
  // dl_test_is_empty();
  // dl_test_is_full();
  return 0;
}