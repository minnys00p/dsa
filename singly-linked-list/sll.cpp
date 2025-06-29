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
    public: 
        // Displays all the elements in the list
        void print() {
            // CASE 1: List is empty
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

        // Appends a new node at the back of the list
        void push_back(int val) {
            Node* new_node = new Node(val);

            // CASE 1: List is empty
            if (head == nullptr) {
                head = new_node;
                return;
            }

            Node* cur = head;
            while (cur->next != nullptr) {
                cur = cur->next;
            }
            cur->next = new_node;
            new_node->next = nullptr;
        }

        // Get the nth item (0-based indexing) in the list
        Node* get_nth(int n) {
            // CASE 1: the list is empty
            if (head == nullptr) { return nullptr; }

            int i = 0;
            Node* cur = head;
            while (cur != nullptr) {
                if (i == n) {
                    return cur;
                }

                cur = cur->next;
                i++;
            }

            // CASE 2: n is outside the range of the list's length
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

            // CASE 1: Value is not in the list
            return -1;
        }

        // Better search, but every time you find the item, you move it one step to the left
        int better_search(int val) {
            int i = 0;
            Node* cur = head;

            // CASE 1: The list is empty
            if (cur == nullptr) return -1;

            // CASE 2: Value is the head
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

        // Another version of better search, but this time it is done while tracking the previous node of the current node (a classic trick)
        int better_search_v2(int val) {
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

        // HOMEWORK (EASY CHALLENGES)

        // List destructor
        ~List() {
            while (head != nullptr) {
                Node* cur = head->next;
                delete head;
                head = cur;
            }
        }

        // Inserts a node at the front of the list
        void insert_front(int val) {
            Node* new_node = new Node(val);
            // CASE 1: The list is empty
            if (head == nullptr) {
                head = new_node;
                return;
            }

            new_node->next = head;
            head = new_node;
        }

        // Deletes the front of the list
        void delete_front() {
            // CASE 1: The list is empty
            if (head == nullptr) {
                return;
            }
            Node* tmp = head;
            head = tmp->next;
            delete tmp;
        }

        // Gets the nth node (1-based indexing) starting from the back
        Node* get_nth_from_end(int n) {
            // CASE 1: n is less than 1
            if (n < 1) { return nullptr; }

            int count = 1;
            Node* lead = head;
            while (count <= n) {
                if (lead == nullptr) {
                    return nullptr;
                }
                lead = lead->next;
                count++;
            }

            Node* ret = head;
            while (lead != nullptr) {
                lead = lead->next;
                ret = ret->next;
            }

            return ret;
        }

        // Get's the head of the current list
        Node* getHead() const {
            // NOTE: 'const' suffix means that this function does not modify THIS list
            return this->head;
        }

        // Checks if provided lists contain the same content
        bool equal(const List& other_list) const {
            // NOTE: 'const' in the parameters means that this function does not modify other_list. 
            Node* tmp1 = head;
            Node* tmp2 = other_list.getHead();
            while (tmp1 != nullptr && tmp2 != nullptr && tmp1->data == tmp2->data){
                tmp1 = tmp1->next;
                tmp2 = tmp2->next;
            }

            return tmp1 == nullptr && tmp2 == nullptr;
        }

        // Deletes the last node from the list
        void delete_last() {
            // CASE 1: List is empty
            if (head == nullptr) { return; }

            // CASE 2: List has one element
            if (head->next == nullptr) {
                delete head;
                head = nullptr;
                return;
            }

            Node* prev = nullptr;
            Node* tmp = head;
            while (tmp->next != nullptr) {
                prev = tmp;
                tmp = tmp->next;
            }
            prev->next = nullptr;
            delete tmp;
        }

        // Deletes the node at index idx
        void delete_nth(int idx) {
            // CASE 0: idx is less than 0
            if (idx < 0) {
                cout << "Index must be a non-negative number";
                return;
            }

            // CASE 1: List is empty
            if (head == nullptr){
                cout << "List is empty";
                return;
            }

            // CASE 2: Delete first element
            if (idx == 0) {
                this->delete_front();
                return;
            }

            int i = 0;
            Node* prev = head;
            while (i < idx - 1) {
                // CASE 3: If the index is larger than or equal to the length of the list
                if (prev->next == nullptr) {
                    cout << "Invalid index\n";
                    return;
                }
                prev = prev->next;
                i++;
            }

            Node* thing_to_delete = prev->next;

            // CASE 4: The thing you want to delete doesen't exist
            // Without this case, delete_nth(len of list) would throw a seg fault. 
            // Trace the code for proof
            if (thing_to_delete == nullptr) {
                cout << "Invalid index\n";
                return;
            }

            prev->next = thing_to_delete->next;
            delete thing_to_delete;
        }

        // Deletes the first occurence of the node with the provided val
        void delete_with_key(int val) {

        }

        // HOMEWORK (MEDIUM CHALLENGES)

        // HOMEWORK (HARD CHALLENGES)


};

int main(){
    List l = List();
    l.print();
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(5);
    l.push_back(7);
    l.insert_front(100);
    l.print();

    List l2 = List();
    l2.print();
    l2.push_back(1);
    l2.push_back(2);
    l2.push_back(3);
    l2.push_back(5);
    l2.push_back(7);
    l2.print();

    l2.delete_nth(5);
    l2.print();


    return 0;
}