#ifndef DEQUE_LIST_HPP
#define DEQUE_LIST_HPP

#include <iostream>
using namespace std;

template <typename T>
class DequeList
{
/* public:
    // Constructor
    //DequeList(int blockSize);

    // Destructor
    //~DequeList();

    // Copy Constructor
    DequeList(const DequeList<T> &other);

    //Copy Assignment Operator
    DequeList& operator=(const DequeList& other);

    // Append element to the left
    void append_left(T element);

    // Append element to the right
    void append_right(T element);

    // Pop element from the left
    T pop_left();

    // Pop element from the right
    T pop_right();

    // Peek at the leftmost element (without removing)
    const T& peek_left() const;

    // Peek at the rightmost element (without removing)
    const T& peek_right() const;

    // Get the number of elements in the deque
    int get_count() const;

    // Print the elements in the deque
    void print() const;

    // Access element at a specific index
    T &at(int index);

    // Check if the deque is full
    bool is_full() const;

    // Check if the deque is empty
    bool is_empty() const; */

private:
    const int MAP_CAPACITY = 4; //Initial Capacity of the Deque
    T** map;         // C-style array of pointers to blocks
    int map_size;    // Current size of the map array
    int block_size;  // Number of elements per block
    int count;       // Number of elements in the deque
    int start_block; // Index of the starting block of the deque
    int end_block;  //Index of the end block of the deque
    int front_index; // Index of the front element in the deque
    int back_index;  // Index of the back element in the deque

    // TO DO: Add additional helper functions as needed

// --------------------------------------------------------------------
//
// Implementation of public functions
//
// --------------------------------------------------------------------

public:

    // Constructor
   // TO DO: change map_capacity to be min capacity that the deque can hold at creation
    DequeList(int blockSize = 4) 
      :  map_size(MAP_CAPACITY), block_size(blockSize), count(0), start_block(0), end_block(1),  front_index(-1), back_index(-1)
    {
       map = new T*[map_size];
       for (int i = 0; i < map_size; i++){
        map[i] = new T[block_size];
       }
    }

    // Destructor
    
    ~DequeList()
    {
        for (int i = 0; i < map_size; i++){
            delete[] map[i];
        }
        delete [] map;
    }

    // copy constructor
    DequeList(const DequeList& other):
        map_size(other.map_size), front_index(other.front_index), back_index(other.back_index), count(other.count), block_size(other.block_size)
    {
        map = new T*[map_size];
        for (int i = 0; i < map_size; i++){
            if (other.map[i] != nullptr){
                map[i] = new T[block_size];
                for (int j = 0; j < block_size; j++){
                    map[i][j] = other.map[i][j];
                }
            }
            else {
                map[i] = nullptr;
            }
        }
    }   


    // copy assignment operator
    DequeList& operator=(const DequeList& other)
    {
        if (this == &other){
            return *this;
        }

        for (int i = 0; i < map_size; i++){
                delete map[i];
        }
        delete [] map;

        map_size = other.map_size;
        block_size = other.block_size;
        front_index = other.front_index;
        back_index = other.back_index;
        count = other.count;
        

        map = new T*[map_size];
        for (int i = 0; i < map_size; i++){
            if (other.map[i] != nullptr){
                map[i] = new T[block_size];
                for (int j = 0; j < block_size; j++){
                    map[i][j] = other.map[i][j];
                }
            }
            else {
                map[i] = nullptr;
            }
        }
        return *this;
    }

   void print()
{
    if (is_empty()) {
        std::cout << "Deque is empty" << std::endl;
        return;
    }

    // Print elements from start_block to end_block
    int block = start_block;
    int index = front_index;
  


    cout << "Current Deque: ";
    // Traverse from start_block to end_block
    while (true) {
        // Print elements in the current block
        int limit = (block == end_block) ? back_index + 1 : block_size; // Handle end block differently
        for (int i = (block == start_block ? front_index : 0); i < limit; i++) {
            std::cout << map[block][i] << " ";
        }
        
        // Move to the next block
        block = (block + 1) % map_size;
        
        // Stop if we have traversed all blocks or reached the end_block
        if (block == (end_block + 1) % map_size) break;
    }

    cout << endl;
    cout << "front_index " << front_index << " back_index " << back_index
              << " count " << count << " map_size " << map_size
              << " block_size " << block_size << " start_block " << start_block
              << " end_block " << end_block << endl;
    cout << endl;
}
  
    /*
    TO DO: refactor common functionality between append_left & append_right
    */
    void append_left(T element)
    {
        if (is_empty()){
            map[0] = new T[block_size];
            front_index = 0; //front index of the block
            back_index = front_index; // back index of the block
            start_block = 0;
            map[0][front_index] = element;
        }
        else{
            // checking if the block is full
            if (front_index == 0){
                // expanding map if it doesn't have enough space for another block
                if (count / block_size >= map_size){
                    T** new_map = new T*[map_size +1];
                    // making room for a new block at front
                    for (int i = 0; i < map_size; i++){
                        new_map[i+1] = map[i];
                    }
                    // adding new block
                    new_map[0] = new T[block_size];
                    delete [] map;
                    map = new_map;
                    map_size++;
                }
                else{
                    // making room for new  block
                    for (int i = map_size-1; i >= 0; i--){
                        map[i+1] = map[i];
                    }
                    // adding new block
                    map[0] = new T[block_size];
                }
                // now front is last element of new block
                start_block = 0;
                front_index = block_size-1; 
                back_index = (back_index + 1) % map_size;   

            }
            else{
                front_index--;
            }
            // adding element to to block
            map[start_block][front_index] = element;
        }
        count++;
    }

    void append_right(T element){
        if (is_empty()){
            map[0]= new T[block_size];
            back_index = 0;
            end_block = 0;
            front_index = back_index;
            map[back_index][back_index] = element;
        }
        else{
            // check if the block is full 
            if (back_index == block_size -1){
                // check if map is full on right
                if (count/block_size >= map_size){
                    T** new_map = new T*[map_size +1];
                    // copying elements to new map and adding new block
                    for (int i = 0; i < map_size; i++){
                        new_map[i] = map[i];
                    }
                    new_map[map_size] = new T[block_size];
                    delete [] map;
                    map = new_map;
                    map_size++;
                }
                // now back is first element of new block and end block is the next block on the right
                end_block = (end_block +1) % map_size;
                back_index = 0;
                

            }
            else {
                back_index++;
            }
            // Find the current end block where we need to add the element
            map[end_block][back_index] = element;
        }
        count++;
    }

    T pop_left()
    {
        if (is_empty()){
            throw out_of_range("Deque is empty");
        }

        T val = map[start_block][front_index];
        front_index++;
        count--;
        if (front_index == block_size){
            start_block = (start_block + 1) % map_size;
            front_index = 0;
        }
        if (count == 0){
            front_index = -1;
            back_index = -1;
        }
        return val;
    }

    
    T pop_right()
    {
         if (is_empty()){
            throw out_of_range("Deque is empty");
        }

        T val = map[end_block][back_index];
        back_index--;
        count--;

        if (back_index < 0){
            back_index = block_size -1; 
            end_block = (end_block -1 + map_size) % map_size;
        }
        if (count == 0){
            front_index = -1;
            back_index = -1;
        }
        return val;
    }

    
    const T& peek_left() const
    {
        if (count == 0){
           throw runtime_error("cannot peek empty deque"); 
        }
        return map[start_block][front_index];
    }

    const T& peek_right() const
    {
        if (count == 0){
           throw runtime_error("cannot peek empty deque");
        }
        return map[end_block][back_index];
    }

    int get_count() const
    {
        return count;
    }
    
    T& at(int index)
    {
        int block = index/block_size;
        int block_position = index % block_size;
        return map[block][block_position];
    }

    bool is_empty() const
    {
        return (count == 0);
    }

   bool is_full() const
   {
      return (count == map_size * block_size); 
   }

   int get_capacity() const
   {
    return map_size * block_size;
   }

};

#endif // DEQUE_LIST_HPP
