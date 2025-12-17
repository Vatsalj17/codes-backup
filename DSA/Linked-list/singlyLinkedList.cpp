#include <iostream>
using namespace std;

class Node {
   public:
	int data;
	Node* next;

	Node(int data) {
		this->data = data;
		this->next = NULL;
	}

    ~Node() {
        int value = this->data;
        if (this->next != NULL) {
            delete next;
            this->next = NULL;
        }
        cout << "Memory is free for node with data " << value << endl;
    }
};

void insertNodeAtHead(Node*& head, int data) {
	Node* temp = new Node(data);
	temp->next = head;
	head = temp;
}

void insertNodeAtTail(Node*& tail, int data) {
	Node* temp = new Node(data);
	tail->next = temp;
	tail = tail->next;
}

void insertAtPosition(Node*& head, Node*& tail, int pos, int data) {
    if (pos == 1) {
        insertNodeAtHead(head, data);
        return;
    }
	Node* temp = head;
	for (int i = 1; i < pos - 1; i++) {
		temp = temp->next;
	}
    if (temp->next == NULL) {
        insertNodeAtTail(tail, data);
        return;
    }
	Node* nodeToInsert = new Node(data);
	nodeToInsert->next = temp->next;
	temp->next = nodeToInsert;
}

void deleteNodeByPosition(Node*& head, int pos) {
	if (pos == 1) {
        Node* temp = head;
        head = head->next;
        temp->next = NULL;
        delete temp;
	} else {
        Node* curr = head;
        Node* prev = NULL;
        for (int i = 1; i < pos; i++) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
        curr->next = NULL;
        delete curr;
	}
}

void deleteNode(Node*& head, Node* nodeToDelete) {
    if (head == nodeToDelete) {
        head = nodeToDelete->next;
        nodeToDelete->next = NULL;
        delete nodeToDelete;
        return;
    } else {
        Node* temp = head;
        while(temp != NULL && temp->next != nodeToDelete) {
            temp = temp->next;
        }
        if (temp == NULL) return;
        temp->next = nodeToDelete->next;
        nodeToDelete->next = NULL;
        delete nodeToDelete;
    }
}

int length(Node*& head) {
    int count = 0;
    Node* temp = head;
    while(temp != NULL) {
        temp = temp->next;
        count++;
    }
    return count;
}

Node* findFirstOccurance(Node*& head, int val) {
    Node* temp = head;
    while(temp->data != val) {
        temp = temp->next;
    }
    return temp;
}

void printList(Node* head) {
	Node* temp = head;
	while (temp != NULL) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}

int main(void) {
	Node* node = new Node(4);
	Node* head = node;
	Node* tail = node;
	insertNodeAtHead(head, 10);
	insertNodeAtHead(head, 19);
	insertNodeAtTail(tail, 7);
	insertNodeAtTail(tail, 8);
	insertAtPosition(head, tail, 2, 78);
	deleteNodeByPosition(head, 1);
    deleteNode(head, findFirstOccurance(head, 10));
	printList(head);
}
