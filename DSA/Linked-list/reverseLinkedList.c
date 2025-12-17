#include <stdio.h>
#include <stdlib.h>

#include "list.h"

// optimized approach
struct ListNode* reverse(struct ListNode* head) {
    if (head == NULL || head->next == NULL) return head;
    struct ListNode* nextHead = reverse(head->next);
    head->next->next = head;
    head->next = NULL;
    return nextHead;
}

struct ListNode* reverseList(struct ListNode* head) {
    return reverse(head);    
}


// recursion logic
void reverse2(struct ListNode** head, struct ListNode* curr, struct ListNode* prev) {
    if (curr == NULL) {
        *head = prev;
        return;
    }
    struct ListNode* temp = curr->next;
    curr->next = prev;
    prev = curr;
    curr = temp;
    reverse2(head, curr, prev);
}

struct ListNode* reverseListRec(struct ListNode* head) {
    if (head == NULL || head->next == NULL) return head;
    struct ListNode* prev = NULL;
    struct ListNode* curr = head;
    reverse2(&head, curr, prev);
    return head;
}


// loop logic
struct ListNode* reverseListLoop(struct ListNode* head) {
    if (head == NULL || head->next == NULL) return head;
	struct ListNode* new;
	struct ListNode* prev = head;
	struct ListNode* curr = prev->next;
	struct ListNode* temp = NULL;
	prev->next = NULL;
	while (curr != NULL) {
		temp = curr->next;
		curr->next = prev;
		prev = curr;
		curr = temp;
	}
	new = prev;
	return new;
}


int main(void) {
	node_t** nodes = inputList();
	node_t* head = nodes[0];
	printf("Loading the output...\n");
	node_t* new_head = reverseList(head);
	printf("The list: ");
	printList(new_head);
}
