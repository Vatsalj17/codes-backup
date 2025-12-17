#ifndef LIST_HPP
#define LIST_HPP

class Node {
   public:
	int val;
	Node* next;
	Node() : val(0), next(nullptr) {}
	Node(int x) : val(x), next(nullptr) {}
	Node(int x, Node* next) : val(x), next(next) {}
};

void printList(Node* head);
void insertAtHead(Node*& head, int value);
void insertAtTail(Node*& tail, int value);
Node* inputList();

#endif
