#include <iostream>

#include "list.hpp"
using namespace std;

Node* reverse(Node* head, int i, int k) {
	if (head == NULL || head->next == NULL) return head;
	if (i == k) {
		cout << "Got i equals k\n";
		head->next->next = head->next;
		i = 0;
	}
	if (head == NULL || head->next == NULL) return head;
	struct Node* nextHead = reverse(head->next, i + 1, k);
	head->next->next = head;
	head->next = NULL;
	return nextHead;
}

Node* kReverse(Node* head, int k) {
	if (head == NULL) return NULL;
	if (k <= 1) return head;
	Node* prev = NULL;
	Node* curr = head;
	Node* next = NULL;
	Node* temp = head;
	int count = 0;
	while (temp != NULL && count < k) {
		temp = temp->next;
		count++;
	}
	if (count < k) return head;
	count = 0;
	while (curr != NULL && count < k) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
		count++;
	}
	if (next != NULL) head->next = kReverse(next, k);
	return prev;
}

int main(void) {
	Node* head = inputList();
	int k;
	cout << "Enter k: ";
	cin >> k;
	cout << "Loading the output....\n";
	Node* new_head = kReverse(head, k);
	printList(new_head);
}
