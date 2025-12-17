#include <iostream>
using namespace std;

class Node {
    public:
    int data;
    Node *next;

    Node (int value) {
        this->data = value;
        this->next = NULL;
    }
    ~Node () {
        int value = this->data;
        if (this->next != NULL) {
            delete next;
            next = NULL;
        }
        cout << "Node with value " << value << " is deleted\n";
    }
};

void insertNode(Node*& tail, int element, int data) {
    if (tail == NULL) {
        Node* newNode = new Node(data);
        tail = newNode;
        newNode->next = newNode;
        return;
    }
    Node* curr = tail;
    while (curr->data != element) curr = curr->next;
    Node* temp = new Node(data);
    temp->next = curr->next;
    curr->next = temp;
}

void deleteNode(Node*& tail, int value) {
    if (tail == NULL) {
        cout << "List is empty\n";
        return;
    }
    Node *prev = tail;
    Node *curr = tail->next;
    while (curr->data != value) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = curr->next;

    if (curr == prev) tail = NULL;
    if (tail == curr) tail = prev;

    curr->next = NULL;
    delete curr;
}

void printList(Node* tail) {
    Node* temp = tail;
    do {
        cout << tail->data << " ";
        tail = tail->next;
    } while (tail != temp);
    cout << endl;
}

int main(void) {
    Node* tail = NULL;
    insertNode(tail, 5, 3);
    insertNode(tail, 3, 9);
    insertNode(tail, 9, 7);
    insertNode(tail, 3, 1);
    insertNode(tail, 9, 6);
    insertNode(tail, 9, 10);
    insertNode(tail, 1, 23);
    insertNode(tail, 9, 97);
    deleteNode(tail, 23);
    printList(tail);
}
