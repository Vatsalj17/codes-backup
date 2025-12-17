#include "list.hpp"
#include <iostream>
using namespace std;

void printList(Node* head) {
    Node* temp = head;
    while (temp) {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;
}

void insertAtHead(Node*& head, int value) {
    Node* node = new Node(value);
    node->next = head;
    head = node;
}

void insertAtTail(Node*& tail, int value) {
    Node* node = new Node(value);
    if (tail) tail->next = node;
    tail = node;
}

Node* inputList() {
    int n;
    cout << "Enter the lenght of list: ";
    cin >> n;
    if (n <= 0) return nullptr;
    int val;
    cout << "Enter the list: ";
    cin >> val;
    Node* head = new Node(val);
    Node* tail = head;
    for (int i = 1; i < n; i++) {
        cin >> val;
        insertAtTail(tail, val);
    }
    return head;
}
