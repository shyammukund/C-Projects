#include "deque.hpp"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <cctype>
#include <stdexcept>

using std::cout;
using std::endl;

// Constructor
Deque::Deque(int initialCapacity) : 
    left(-1), count(0),  capacity(initialCapacity)
{
    arr = new int[capacity];
}

// Destructor
Deque::~Deque()
{
    delete[] arr;
}

void Deque::resize(){
    int new_capacity = capacity * 2;
    int* new_array = new int[new_capacity];

    // centers the elements of the old array in the new array
    for (int i = 0; i < capacity; i++){
        new_array[i+ (new_capacity/4)] = arr[i];
    }
    delete[] arr;
    arr = new_array;
    capacity = new_capacity; 
    left = capacity/4; 
    
    
}

// Helper method to print the state of deque
void Deque::print() const
{
    // Implementation goes here
    int right = left + count -1;
    for (int i = left; i <= right; i++){
        if (i != right){
            std::cout << arr[i] << ", ";
        }
        else{
            std::cout << arr[i]; 
        }
    }
    cout << endl;
    cout << "left "  << left  << " " << "right " << right << " " << "count " << count << " " <<  "capacity " << capacity << endl;
     
}

// Method to append an element to the left
void Deque::append_left(int element)
{
    // Implementation goes here
    if (is_empty()){
        left = capacity/2;
        arr[left] = element;
    }
    else if (count == capacity){
        resize();
        left--;
        arr[left] = element;
    }
    else{
        left--;
        arr[left] = element;
    }
    count++;
    return;
}

// Method to append an element to the right
void Deque::append_right(int element)
{
    // Implementation goes here
    int right = -1;
    if (is_empty()){
        right = capacity/2;
        left = right;
        arr[right] = element;
    }
    else if (count == capacity){
        resize();
        right = left + count -1;
        right++;
        arr[right] = element;
    }
    else{
        right = left + count -1;
        right++;
        arr[right] = element;
    }
    count++;

}

// Method to pop an element from the left
int Deque::pop_left()
{
    // Implementation goes here
    int val = arr[left];
    left++;
    count--;
    if (count == 0){
        left = -1;
    }
    return val;
    
}

// Method to pop an element from the right
int Deque::pop_right()
{
    
    int right = left + count -1;
    int val = arr[right];
    right--;
    count--;
    if (count == 0){
        left = -1;
    }
    return val;
}

// Method to peek at the leftmost element
int Deque::peek_left() const
{
    // Implementation goes here
    if (count == 0){
        throw std:: runtime_error("cannot peek empty deque");
    }
    return arr[left];
    
     // Placeholder return
}

// Method to peek at the rightmost element
int Deque::peek_right() const
{
    // Implementation goes here
     if (count == 0){
        throw std:: runtime_error("cannot peek empty deque");
    }
    return arr[left + count -1];
}

// Method to get the count of elements in the deque
int Deque::get_count() const
{
    return count;
}

// Helper method to check if deque is full
bool Deque::is_full() const
{
    // Implementation goes here
    
    return (count == capacity); // Placeholder return
}

// Helper method to check if deque is empty
bool Deque::is_empty() const
{
    // Implementation goes here
    return (count == 0); // Placeholder return
}


