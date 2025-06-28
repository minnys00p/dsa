#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next = nullptr;
    Node(int data): data(data){}
};

class List {
    private:
        Node* head = nullptr;
        Node* tail = nullptr;
        int length = 0;
    public: 
        List() {}
        ~List() {}

        void print() {
            if (head == nullptr) {
                cout << "No elements to display.\n";
                return;
            }
            
            Node* tmp = head;
            while (tmp != nullptr){
                cout << tmp->data << " ";
                tmp = tmp->next;
            }
            cout << "\n";
        }

        void push(int val) {
            Node* new_node = new Node(val);
            length++;

            // CASE 1: Head/tail is initial
            if (head == nullptr) {
                head = new_node;
                tail = head;
                
                return;
            }

            // CASE 2: Head/tail is not empty
            tail->next = new_node;
            tail = new_node;
        }

        int getLength(){
            return this->length;
        }

        // Get the nth item in the list
        Node* get_nth(int n) {
            int i = 0;
            Node* cur = head;
            while (cur != nullptr) {
                if (i == n) {
                    return cur;
                }

                cur = cur->next;
                i++;
            }
            return nullptr;
        }

        // Get the index of the first occurence of the provided value, -1 otherwise
        int search(int val) {
            int i = 0;
            for (Node* cur = head; cur != nullptr; cur = cur->next, i++){
                if (cur->data == val) {
                    return i;
                }
            }
            return -1;
        }

        // Improved search, but every time you find the item, you move it one step to the left
        int better_search(int val) {
            int i = 0;
            Node* cur = head;

            // CASE 1: val is at the head
            if (cur->data == val) {
                return 0;
            }

            Node* x = head->next; 
            while (x != nullptr) {
                if (x->data == val) {
                    int tmp = cur->data;
                    cur->data = x->data;
                    x->data = tmp;
                    return i;
                }

                i++;
                x = x->next;
                cur = cur->next;
            }
            return -1;
        }

        int better_search_v2(int val) {
            // This time try to do it with a Node pointing to the previous of the current Node
            int i = 0;
            Node* cur = head;
            Node* prev = nullptr;
            for (;cur != nullptr; prev = cur, cur = cur->next, i++) {
                if (cur->data == val) {
                    if (prev == nullptr) {
                        return i;
                    }

                    swap(prev->data, cur->data);
                    return i - 1;
                }
            }

            return -1;
        }

};

int main(){
    List l = List();
    l.print();
    l.push(1);
    l.push(2);
    l.push(3);
    l.push(5);
    l.push(7);
    l.push(11);

    l.print();
    cout << l.better_search_v2(11) << "\n";
    l.print();


    return 0;
}