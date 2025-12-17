#ifndef LIST_H
#define LIST_H

typedef struct ListNode {
    int val;
    struct ListNode *next;
}node_t;

void printList(node_t* head);
node_t* createNode(int value);
void insertAtHead(node_t** head, int value);
void insertAtTail(node_t** tail, int value);
node_t** inputList();

#endif
