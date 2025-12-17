#include <iostream>
using namespace std;

class Node {
   public:
	int data;
	Node* prev;
	Node* next;

	Node(int value) {
		this->data = value;
		this->prev = NULL;
		this->next = NULL;
	}
    ~Node() {
        int value = this->data;
        if (this->next != NULL) {
            delete next;
            this->next = NULL;
        }
        cout << "Memory of value " << value << " was deleted\n";
    }
};

void insertNodeAtHead(Node*& head, Node*& tail, int data) {
    if (head == NULL) {
        Node* temp = new Node(data);
        head = temp;
        tail = temp;
        return;
    }
	Node* temp = new Node(data);
	temp->next = head;
    head->prev = temp;
	head = temp;
}

void insertNodeAtTail(Node*& tail, Node*& head, int data) {
    if (head == NULL) {
        Node* temp = new Node(data);
        head = temp;
        tail = temp;
        return;
    }
	Node* temp = new Node(data);
	tail->next = temp;
    temp->prev = tail;
	tail = temp;
}

void insertAtPosition(Node*& head, Node*& tail, int pos, int data) {
    if (pos == 1) {
        insertNodeAtHead(head, tail, data);
    }
	Node* temp = head;
	for (int i = 1; i < pos - 1; i++) {
		temp = temp->next;
	}
    if (temp->next == NULL) {
        insertNodeAtTail(tail, head, data);
        return;
    }
	Node* nodeToInsert = new Node(data);
	nodeToInsert->next = temp->next;
    temp->next->prev = nodeToInsert;
	nodeToInsert->prev = temp;
	temp->next = nodeToInsert;
}

void deleteNodeByPosition(Node*& head, int pos) {
	if (pos == 1) {
        Node* temp = head;
        temp->next->prev = NULL;
        head = head->next;
        temp->next = NULL;
        delete temp;
	} else {
        Node* curr = head;
        for (int i = 1; i < pos; i++) {
            curr = curr->next;
        }
        curr->prev->next = curr->next;
        if (curr->next != NULL)
            curr->next->prev = curr->prev;
        curr->next = NULL;
        curr->prev = NULL;
        delete curr;
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

void printList(Node* head) {
	Node* temp = head;
	while (temp != NULL) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}

int main(void) {
	Node* node1 = new Node(5);
    Node* head = node1;
    Node* tail = node1;
    insertNodeAtHead(head, tail, 9);
    insertNodeAtTail(tail, head, 45);
    insertAtPosition(head, tail, 3, 33);
    insertNodeAtHead(head, tail, 73);
    deleteNodeByPosition(head, 3);
    printList(head);
    cout << "length: " << length(head) << endl;
}
