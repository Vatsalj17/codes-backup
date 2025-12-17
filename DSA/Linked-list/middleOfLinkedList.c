#include <stdio.h>
#include "list.h"

struct ListNode* middleNode(struct ListNode* head) {
    struct ListNode* temp = head;
    struct ListNode* mid = head;
    int count = 0;
    while (temp != NULL) {
        temp = temp->next;
        if (count&1) mid = mid->next;
        count++;
    }
    return mid;
}

void deleteNode(struct ListNode **head, struct ListNode *node_to_remove) {
    if (*head == node_to_remove) {
        *head = node_to_remove->next;
        return;
    } else {
        struct ListNode *temp = *head;
        while(temp != NULL && temp->next != node_to_remove) {
            temp = temp->next;
        }
        if (temp == NULL) return;
        temp->next = node_to_remove->next;
        node_to_remove->next = NULL;
    }
}


struct ListNode* deleteMiddle(struct ListNode* head) {
    struct ListNode* mid = middleNode(head);
    deleteNode(&head, mid);
    return head;
}

int main(void) {
	node_t** nodes = inputList();
	node_t* head = nodes[0];
	printf("Loading the output...\n");
	node_t* new_head = deleteMiddle(head);
	printf("The list: ");
	printList(new_head);
}
