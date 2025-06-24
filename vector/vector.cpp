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
            capacity = capacity*2 + 1;

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
            if (size < 0) { 
                throw "Size must be greater than or equal to 0";
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

        // HOMEWORK
        // Rotates the whole array 1 step to the right. So, 0 1 2 3 4 -> 4 0 1 2 3
        void right_rotate() {
            int back = this->back();

            // Shift everthing to the right
            for (int i = size - 1; i > 0; i--) {
                arr[i] = arr[i-1];
            }

            this->set(0, back);
        }

        // Rotates the whole array 1 step to the left. So, 0 1 2 3 4 -> 1 2 3 4 0
        void left_rotate() {
            int front = this->front();

            // Shift everything to the left
            for (int i = 0; i < size - 1; i++) {
                arr[i] = arr[i+1];
            }

            this->set(size-1, front);
        }

        // Rotates the whole array n number of times
        void right_rotate(int n) {
            // Naive: Call right_rotate() n number of times
            int r = n % size;
            for (int i = 0; i < r; i++) {
                this->right_rotate();
            }
        }

        // Remove the value at the specified index and return the value
        int pop(int idx) {
            // CASE 1: idx < 0 OR idx >= size
            if (idx < 0 || idx >= size) {
                throw "Index out of bounds!";
            }
            int popped_element = arr[idx];

            for (int i = idx; i < size - 1; i++) {
                arr[i] = arr[i+1];
            }

            // Reduce the size because you popped an element
            size--;

            return popped_element;
        }

        // Search for an element and swap it with the left most element if found, -1 otherwise
        int find_transposition(int value) {
            for (int i = 0; i < size-1; i++) {
                if (arr[i] == value) {
                    if (i == 0) {
                        return 0;
                    } 

                    swap(arr[i], arr[i-1]);
                    return i - 1;
                }
            }
            return -1;
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

    Vector increasing_vector = Vector(5);
    for (int i = 0; i < 5; i++) {
        increasing_vector.set(i, i);
    }
    increasing_vector.print();
    cout << "Above vector right rotated...\n";
    increasing_vector.right_rotate();
    increasing_vector.print();
    cout << "Above vector left rotated...\n";
    increasing_vector.left_rotate();
    increasing_vector.print();

    Vector vector_with_three_elements = Vector(3);
    for (int i = 0; i < 3; i++) {
        vector_with_three_elements.set(i,i);
    }
    vector_with_three_elements.print();
    vector_with_three_elements.pop(1);
    cout << "After popping first index: ";
    vector_with_three_elements.print();

    Vector empty_vector = Vector(0);
    empty_vector.print();
    empty_vector.add(1);
    empty_vector.print();
    empty_vector.get(0);
    empty_vector.pop(empty_vector.length()-1);
    empty_vector.print();


    Vector my_vector = Vector(5);
    for (int i = 0; i < 5; i++) {
        my_vector.set(i, i);
    }
    my_vector.print();
    cout << "After rotating it once: ";
    my_vector.right_rotate(1); 
    my_vector.print();
    cout << "\n";
    cout << "After rotating it four more times: ";
    my_vector.right_rotate(4); 
    my_vector.print();
    cout << "\n";

    my_vector.print();
    cout << "\n";
    cout << "Transposition(3): " << my_vector.find_transposition(3) << "\n";
    my_vector.print();
    cout << "\nAgain...\nTransposition(3): " << my_vector.find_transposition(3) << "\n";
    my_vector.print();
    cout << "\nAgain...\nTransposition(3): " << my_vector.find_transposition(3) << "\n";
    my_vector.print();
    cout << "\nAgain...\nTransposition(3): " << my_vector.find_transposition(3) << "\n";
    my_vector.print();
    cout << "\n";
}