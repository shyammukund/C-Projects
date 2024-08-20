#include <iostream>
template <typename T>

class Deque
{
public:
    // Constructor
    Deque(int capacity = 8, int resizeFac = 2);

    // Destructor
    ~Deque();

    //Copy Constructor
    Deque(const Deque& other);
        

    // Method to print
    void print() const;

    // Method to append an element to the left
    void append_left(T element);
      

    // Method to append an element to the right
    void append_right(T element);

    // Method to pop an element from the left
    T pop_left();

    // Method to pop an element from the right
    T pop_right();

    // Method to peek at the leftmost element
    T peek_left() const;

    // Method to peek at the rightmost element
    T peek_right() const;

    // Method to get the count of elements in the deque
    int get_count() const;

    //Method to resize the array
    void resize();



private:
    T* arr;     // Array to store elements
    int left;     // Index of the leftmost element
    int count;    // Number of elements in the deque
    int capacity; // Maximum capacity of the deque
    int resizeFactor;
    // Helper methods
    bool is_full() const;
    bool is_empty() const;

    
    

};

template <typename T> 
Deque<T>::Deque(int initialCapacity,int resizeF) :
    left(-1), count(0), capacity(initialCapacity), resizeFactor(resizeF) 
{
arr = new T[capacity]; 
}

template <typename T>
Deque<T>::~Deque()
{
delete[] arr;
}

//copy constructor
template <typename T> 
Deque<T>::Deque(const Deque& other) :
    left (other.left), count(other.count), capacity(other.capacity), resizeFactor(other.resizeFactor)
{
    T* arr_copy = new T[capacity];
    int i = 0;
    for (T o: other){
        arr_copy[i++];
    }
}



// copy assignment operator
template <typename T>
Deque<T>::Deque(const Deque& other):
{
    if (this == &other){
        return *this;
    }

    delete [] arr;

    left = other.left;
    count = other.count;
    capacity = other.capacity;
    resizeFactor = other.resizeFactor;

    arr* = new T[other.capacity]; 
    int i = 0;
    for (int i = 0; i < capacity; i++){
        arr[i] = other.arr[i];
    }

    return *this;
}




    
   

template <typename T>
void Deque<T>::resize(){
    int new_capacity = capacity * resizeFactor;
    T* new_array = new T[new_capacity];

    // centers the elements of the old array in the new array
    for (int i = 1; i <= capacity; i++){
        new_array[i+ ((new_capacity - count)/2)] = arr[i];
    }
    left = (new_capacity - count)/2; 
    delete[] arr;
    arr = new_array;
    capacity = new_capacity; 
    
    
    
}

template <typename T>
void Deque<T>::print() const
{
    // Implementation goes here
    int right = left + count -1;
    for ( int i = left; i <= right; i++){
        if (i != right){
            std::cout << arr[i] << ", ";
        }
        else{
            std::cout << arr[i]; 
        }
    }
    std::cout << std::endl;
    std::cout << "left "  << left  << " " << "right " << right << " " << "count " << count << " " <<  "capacity " << capacity << std::endl;
    std::cout << std::endl;
     
}

// Method to append an element to the left
template <typename T>
void Deque<T>::append_left(T element)
{
    // Implementation goes here
    if (is_empty()){
        left = capacity/2;
        arr[left] = element;
    }
    else if (count == capacity){
        resize();
        arr[left] = element;
    }
    else{
        left--;
        arr[left] = element;
    }
    count++;
    //print();
    return;
}

// Method to append an element to the right
template <typename T>
void Deque<T>::append_right(T element)
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
        right = left + count;
        arr[right] = element;
    }
    else{
        right = left + count;
        arr[right] = element;
    }
    count++;
    //print();
    return;

}

// Method to pop an element from the left
template <typename T>
T Deque<T>::pop_left()
{
    // Implementation goes here
    T val = arr[left];
    left++;
    count--;
    if (count == 0){
        left = -1;
    }
    return val;
    
}

// Method to pop an element from the right
template <typename T>
T Deque<T>::pop_right()
{
    int right = left + count;
    T val = arr[right];
    count--;
    if (count == 0){
        left = -1;
    }
    return val;
}

// Method to peek at the leftmost element
template <typename T>
T Deque<T>::peek_left() const
{
    // Implementation goes here
    if (count == 0){
        throw std:: runtime_error("cannot peek empty deque");
    }
    return arr[left];
    
     // Placeholder return
}

// Method to peek at the rightmost element
template <typename T>
T Deque<T>::peek_right() const
{
    // Implementation goes here
     if (count == 0){
        throw std:: runtime_error("cannot peek empty deque");
    }
    return arr[left + count -1];
}

// Method to get the count of elements in the deque
template <typename T>
int Deque<T>::get_count() const
{
    return count;
}

// Helper method to check if deque is full
template <typename T>
bool Deque<T>::is_full() const
{
    // Implementation goes here
    
    return (count == capacity); // Placeholder return
}

// Helper method to check if deque is empty
template <typename T>
bool Deque<T>::is_empty() const
{
    // Implementation goes here
    return (count == 0); // Placeholder return
}