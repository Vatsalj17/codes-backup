#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node *next;
	struct node *prev;
} node_t;

void print_list(node_t *head) {
	node_t *temp = head;
	while (temp != NULL) {
		printf("%d, ", temp->value);
		temp = temp->next;
	}
	printf("\n");
}

node_t *create_new_node(int value) {
	node_t *result = (node_t*)malloc(sizeof(node_t));
	result->value = value;
	result->next = NULL;
	result->prev = NULL;
	return result;
}

void insert_at_head(node_t **head, node_t *node_to_insert) {
    node_to_insert->next = *head;
    (*head)->prev = node_to_insert;
    *head = node_to_insert;
}

void insert_at_tail(node_t **tail, node_t *node_to_insert) {
    node_to_insert->prev = *tail;
    (*tail)->next = node_to_insert;
    *tail = node_to_insert;
}

node_t *find_node(node_t *head, int val) {
    node_t *tmp = head;
    while(tmp != NULL) {
        if (tmp->value == val) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

void insert_after_node(node_t *node_to_insert_after, node_t *newnode) {
    newnode->next = node_to_insert_after->next;
    if (newnode->next != NULL) {
        newnode->next->prev = node_to_insert_after;
    }
    newnode->prev = node_to_insert_after;
    node_to_insert_after->next = newnode;
}

void remove_node(node_t **head, node_t *node_to_remove) {
    if (*head == node_to_remove) {
        *head = node_to_remove->next;
        if (*head != NULL) {
            node_to_remove->next->prev = node_to_remove->prev;
        }
        (*head)->prev = NULL;
        return;
    } else {
        node_to_remove->prev->next = node_to_remove->next;
        if (node_to_remove->next != NULL)
            node_to_remove->next->prev = node_to_remove->prev;
    }
    node_to_remove->next = NULL;
    node_to_remove->prev = NULL;
}

int main() {
	node_t *head = NULL;
    node_t *tail = NULL;
	node_t *tmp = create_new_node(-1);
    head = tmp;
    tail = tmp;
	for (int i = 0; i < 10; i++) {
		tmp = create_new_node(i);
        insert_at_head(&head, tmp);
		// tmp->next = head;
		// head = tmp;
	}
    tmp = create_new_node(-21);
    insert_at_tail(&tail, tmp);
    // node_t *newNode = create_new_node(78);
    // tmp = insert_at_head(&head, newNode);
    // node_t *found = find_node(head, 5);
    // if (found) printf("Node found with value %d\n", found->value);
    // else printf("Node not found\n");
    // insert_after_node(found, create_new_node(86));
    // remove_node(&head, find_node(head, 9));
	print_list(head);
	return 0;
}
