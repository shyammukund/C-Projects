#include <iostream>
#include <cassert>
#include "deque.hpp"

using namespace std;
void test_full(){
    cout << "Hello" << endl;
    Deque deq(5);
    for (int i = 1; i <= 5; i++) {
        deq.append_left(i);
        deq.append_right(i);
    }
    deq.print();


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
void test_basic(){
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
}




int main(int , char** ) 
{
    test_full();
    return 0;
}