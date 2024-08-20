#ifndef DEQUE_LIST_HPP
#define DEQUE_LIST_HPP

#include <iostream>
using namespace std;

template <typename T>
class DequeList
{
public:
    // Constructor
    DequeList(int blockSize);

    // Destructor
    ~DequeList();

    // Copy Constructor
    DequeList(const DequeList<T> &other);


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
    bool is_empty() const;

private:
    T** map;         // C-style array of pointers to blocks
    int map_size;    // Current size of the map array
    int block_size;  // Number of elements per block
    int count;       // Number of elements in the deque
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
    template <typename T>
    DequeList<T>::DequeList(int blockSize) 
      :  map_size(1), block_size(blockSize), count(0), front_index(-1), back_index(-1)
    {
       map = new T*[map_size];
       for (int i = 0; i < map_size; i++){
        map[i] = nullptr;
       }
    }

    // Destructor
    template<typename T> 
    DequeList<T>::~DequeList()
    {
        for (int i = 0; i < map_size; i++){
            delete[] map[i];
        }
        delete [] map;
    }

    template <typename T>
    DequeList<T>:: DequeList(const DequeList& other):
        map_size(other.map_size), front_index(other.front_index), back_index(other.back_index), count(other.count), block_size(other.block_size)
    {
        map = new T*[capacity];
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
    template <typename T>
    DequeList<T>::DequeList(const DequeList& other):
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

    template <typename T>
    void Deque<T>::print() const
    {
    // Implementation goes here
    for (T block: map){
        if (block != nullptr){
            for (int j = 0; j < block_size; j++){
                cout << block[j] << " ";
            }
        }
    }
    std::cout << std::endl;
    std::cout << "front index "  << front_index  << " " << "back index " << back_index << " " << "count " << count << " " <<  "map_size " << map_size << "block_size " << block_size << std::endl;
    std::cout << std::endl;
     
    }

    template <typename T> 
    void DequeList<T>::append_left(T element)
    {
        if (is_empty()){
            map[0] = new T[block_size];
            front_index = 0; //front index of the block
            back_index = front_index; // back index of the block
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
                front_index = block_size -1;
                

            }
            else{
                front_index--;
            }
            // adding element to to block
            map[0][front_index] = element;
        }
        count++;
    }

    template <typename T>
    void DequeList<T>::append_right(T element){
        if (is_empty()){
            map[1]= new T[block_size];
            back_index = 0;
            front_index = back_index;
            map[back_index][back_index] = element;
        }
        else{
            // check if the block is full 
            if (back_index == block_size - 1){
                // check if map has room for a new block
                if (count/block_size >= map_size){
                    T** new_map = new T*[map_size +1];
                    // copying elements to new map and adding new block
                    for (int i = 0; i < map_Size; i++){
                        new_map[i] = map[i];
                    }
                    new_map[map_size] = new T[block_size];
                    delete [] map;
                    map = new_map;
                    map_size++;
                }
                else{
                    // going to the first empty block in map
                    int current = 0;
                    for (int i = 0; i < map_size; i++){
                        if (map[i] == nullptr){
                            current = i;
                            break;
                        }
                    }
                    // adding new block
                    map[current] = new T[block_size];
                }
                // now back is first element of new block
                back_index = 0;

            }
            else {
                back_index++;
            }
            // Find the current block where we need to add the element
            int curBlock = 0;
            for (int c = 0; c < map_size; c++){
                if (map[c] == nullptr){
                    break;
                }
                curBlock = c;
            }
            map[curBlock][back_index] = element;
        }
        count++;
    }
    template <typename T>
    T DequeList<T>:: pop_left()
    {
        if (is_empty()){
            throw out_of_range("Deque is empty");
        }

        T val = map[0][front_index];
        front_index++;
        count--;

        if (front_index == block_size){
            delete[] map[0];
            for (int i = 1; i < map_size; i++){
                map[i-1] = map[i];
            }
            map[map_size-1] = nullptr;
            front_index = 0;
        }
        if (count == 0){
            front_index = -1;
            back_index = -1;
        }
        return val;
    }

    template <typename T>
    T DequeList<T>:: pop_right()
    {
         if (is_empty()){
            throw out_of_range("Deque is empty");
        }

        int curBlock = (count-1)/block_size;
        T val = map[curBlock][back_index];
        back_index--;
        count--;

        if (back_index < 0 && curBlock > 0){
            delete[] map[curBlock];
            map[curBlock] = nullptr;
            back_index = block_size -1;
        }
        if (count == 0){
            front_index = -1;
            back_index = -1;
        }
        return val;
    }

    template<typename T>
    const T& DequeList<T>::peek_left() const
    {
        if (count == 0){
           throw runtime_error("cannot peek empty deque");
        }
        return map[0][front_index];
    }

    template<typename T>
    const T& DequeList<T>::peek_right() const
    {
        if (count == 0){
           throw runtime_error("cannot peek empty deque");
        }
        int curBlock = (count-1)/block_size;
        return map[curBlock][back_index];
    }

    template <typename T>
    int DequeList<T>:: get_count() const
    {
        return count;
    }
    
    template<typename T>
    T& DequeList<T>:: at(int index)
    {
        int block = index/block_size;
        int block_position = index % block_size;
        return map[block][block_position];
    }

    template <typename T>
    bool DequeList<T>: is_empty() const
    {
        if (count == 0){
            return true;
        }
    }

   template <typename T>
   bool DequeList<T>:: is_full() const
   {
    if (count == map_size * block_size){
        return true;
    }
   }


};



#endif // DEQUE_LIST_HPP
