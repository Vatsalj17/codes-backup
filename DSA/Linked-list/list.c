#include "list.h"
#include <stdio.h>
#include <stdlib.h>

void printList(node_t* head) {
    node_t* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");
}

node_t* createNode(int value) {
    node_t* newNode = malloc(sizeof(node_t));
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

void insertAtHead(node_t** head, int value) {
    node_t* new = createNode(value);
    new->next = *head;
    *head = new;
}

void insertAtTail(node_t** tail, int value) {
    node_t* new = createNode(value);
    (*tail)->next = new;
    *tail = new;
}

node_t** inputList() {
	printf("Enter total length of list: ");
	int n;
	scanf("%d", &n);
    if (n <= 0) return NULL;
    node_t** the_list = malloc(2 * sizeof(node_t*));
    printf("Enter the list: ");
    int data;
    scanf("%d", &data);
    node_t* first = createNode(data);
    node_t* head = first;
    node_t* tail = first;
    for (int i = 0; i < n - 1; i++) {
        int d;
        scanf(" %d", &d);
        insertAtTail(&tail, d);
    }
    the_list[0] = head;
    the_list[1] = tail;
    return the_list;
}
