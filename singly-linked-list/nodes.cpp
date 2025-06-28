#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int data) : data(data) {}
};

// Prints the singly linked list
void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << "\n";
}

// Recursively prints the singly linked list
void printListRecursive(Node* head) {
    if (head == nullptr) { 
        cout << "\n";
        return; 
    }
    cout << head->data << " ";
    head = head->next;
    printListRecursive(head);
}

// Recursively prints the single linked list but in reverse order
void printListReversedRecursive(Node* head){
    if (head == nullptr) {
        return;
    }
    printListReversedRecursive(head->next);
    cout << head->data << " ";
}

// Search that returns the node with the value
Node* findFirstNodeWithValue(int val, Node* head) {
    while (head != nullptr) {
        if (head->data == val) {
            return head;
        } 
        head = head->next;
    }
    return nullptr;
}

int main(){
    Node* n1 = new Node(6);
    Node* n2 = new Node(10);
    Node* n3 = new Node(15);
    Node* n4 = new Node(20);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = nullptr;

    printList(n1);
    printListRecursive(n1);
    printListReversedRecursive(n1);
    cout << "\n";
    Node* n = findFirstNodeWithValue(20, n1);
    cout << n->data << "\n";

    return 0;
}