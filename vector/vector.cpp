#include <iostream>
#include <utility> 

using namespace std;

class Vector {
    private:
        int* arr = nullptr; // The actual data
        int size = 0; // Represents the current size of the vector
        int capacity = 0; // Represents the amount of memory allocated to the vector

        // Doubles the capacity of the vector
        void expand_capacity() {
            // Increase the capacity
            capacity = capacity*2;

            // Create a temporary array with the increased capacity
            int* tmp = new int[capacity];
            
            // Copy contents from the current array into the tmp
            for (int i = 0; i < size; i++) { tmp[i] = arr[i];}

            // Swap the pointers of arr and tmp
            swap(arr, tmp);

            delete[] tmp;
        }
    public:
        // Constructor
        Vector(int size): size(size), capacity(size) {
            // CASE 1: size <= 0
            if (size <= 0) { 
                throw "Size must be greater than 0";
            }

            arr = new int[capacity] { }; // Sets all elements to 0
        }

        // Frees memory when object is destroyed
        ~Vector(){
            delete[] arr;
            arr = nullptr;
            size = 0;
            capacity = 0;
        }

        // Returns the vector's current size
        int length() {
            return this->size;
        }

        // Prints the content of the vector
        void print() {
            cout << "{ ";
            for (int i = 0; i < size; i++) {
                cout << arr[i] << " ";
            }
            cout << "}\n";
        }

        // Returns the value at the specified index
        int get(int idx) {
            // CASE 1: idx < 0 OR idx >= size
            if (idx < 0 || idx >= size) {
                throw "Index out of bounds";
            }
            return arr[idx];
        }

        // Replaces the value at the specified index with the new value
        void set(int idx, int new_value) {
            // CASE 1: idx < 0 OR idx >= size
            if (idx < 0 || idx >= size) {
                throw "Index out of bounds!";
            }

            arr[idx] = new_value;
        }

        // Return the first element of the vector
        int front() {
            // CASE 1: Vector is empty
            if (size == 0) {
                throw "No elements in the vector!";
            }
            return arr[0];
        }
        
        // Return the last element of the vector
        int back() {
            // CASE 1: Vector is empty
            if (size == 0) {
                throw "No elements in the vector!";
            }
            return arr[size-1];
        }

        // Adds a new element to the back of the vector
        void add(int new_value) {
            // CASE 1: There is enough capacity
            if (size != capacity) {
                // Add new element
                arr[size++] = new_value;
                return;
            }

            // Increase the vector's capacity
            expand_capacity();
            
            // Add new element
            arr[size++] = new_value;
        }

        void insert(int idx, int new_value) {
            // CASE 1: idx < 0 OR idx >= size
            if (idx < 0 || idx > size) {
                throw "Index out of bounds!";
            }

            // CASE 2: size + 1 > capacity
            if (size + 1 > capacity) {
                expand_capacity();
            }

            // Shift all elements on the right by 1
            for (int i = size - 1; i >= idx; i--) {
                arr[i+1] = arr[i];
            }

            // Set the new value of array into the index
            arr[idx] = new_value;

            // Increase the size
            size++;
            
        }

        // Returns the memory capacity allocated for this vector
        int get_capacity() {
            return this->capacity;
        }
};


// Test Code
int main(){
    Vector vector_with_ten_elements = Vector(10);
    Vector vector_with_one_element = Vector(1);

    vector_with_one_element.add(2);
    vector_with_one_element.add(5);
    vector_with_one_element.add(6);
    vector_with_one_element.add(10);
    vector_with_one_element.print();
    cout << "Vector with one element size: " << vector_with_one_element.length() << "\n";
    cout << "Vector with one elements capacity: " << vector_with_one_element.get_capacity() << "\n";


    vector_with_ten_elements.insert(0,10);
    for (int i = 1; i < vector_with_ten_elements.length(); i++) {
        vector_with_ten_elements.set(i, i);
    }
    vector_with_ten_elements.print();

    vector_with_ten_elements.insert(vector_with_ten_elements.length(), 41);
    vector_with_ten_elements.print();
    cout << "Vector with ten elements size: " << vector_with_ten_elements.length() << "\n";
    cout << "Vector with ten elements capacity: " << vector_with_ten_elements.get_capacity() << "\n";
}