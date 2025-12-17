#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct ListNode* createNode(int value) {
    struct ListNode* newNode = malloc(sizeof(struct ListNode));
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

void insertAtTail(struct ListNode** tail, int value) {
    struct ListNode* new = createNode(value);
    (*tail)->next = new;
    *tail = new;
}

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
	int carry = 0;
	int value = l1->val + l2->val;
	if (value >= 10) {
		carry = value / 10;
		value %= 10;
	}
	struct ListNode* ans = createNode(value);
	struct ListNode* tail = ans;
	struct ListNode* temp1 = l1->next;
	struct ListNode* temp2 = l2->next;
	while (temp1 != NULL && temp2 != NULL) {
		int value = temp1->val + temp2->val;
		value += carry;
		carry = value / 10;
		value = value % 10;
		insertAtTail(&tail, value);
		temp1 = temp1->next;
		temp2 = temp2->next;
	}
    while (temp1 != NULL) {
        value = carry + temp1->val;
		carry = value / 10;
		value = value % 10;
		insertAtTail(&tail, value);
		temp1 = temp1->next;
    }
    while (temp2 != NULL) {
        value = carry + temp2->val;
		carry = value / 10;
		value = value % 10;
		insertAtTail(&tail, value);
		temp2 = temp2->next;
    }
    if (carry) insertAtTail(&tail, carry);
	return ans;
}

int main(void) {
	node_t** nodes = inputList();
	node_t* head = nodes[0];
	node_t** nodes1 = inputList();
	node_t* head1 = nodes1[0];
	printf("Output Loading....\n");
	node_t* ans = addTwoNumbers(head, head1);
	printf("Output: ");
	printList(ans);
}
