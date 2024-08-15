#pragma once

class Deque
{
public:
    // Constructor
    Deque(int capacity = 8);

    // Destructor
    ~Deque();

    // Method to print
    void print() const;

    // Method to append an element to the left
    void append_left(int element);
      

    // Method to append an element to the right
    void append_right(int element);

    // Method to pop an element from the left
    int pop_left();

    // Method to pop an element from the right
    int pop_right();

    // Method to peek at the leftmost element
    int peek_left() const;

    // Method to peek at the rightmost element
    int peek_right() const;

    // Method to get the count of elements in the deque
    int get_count() const;

    //Method to resize the array
    void resize();



private:
    int *arr;     // Array to store elements
    int left;     // Index of the leftmost element
    int count;    // Number of elements in the deque
    int capacity; // Maximum capacity of the deque

    // Helper methods
    bool is_full() const;
    bool is_empty() const;

    
    

};


