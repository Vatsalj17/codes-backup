#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node *next;
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
	return result;
}

node_t *insert_at_head(node_t **head, node_t *node_to_insert) {
    node_to_insert->next = *head;
    *head = node_to_insert;
    return node_to_insert;
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
    node_to_insert_after->next = newnode;
}

void remove_node(node_t **head, node_t *node_to_remove) {
    if (*head == node_to_remove) {
        *head = node_to_remove->next;
        return;
    } else {
        node_t *temp = *head;
        while(temp != NULL && temp->next != node_to_remove) {
            temp = temp->next;
        }
        if (temp == NULL) return;
        temp->next = node_to_remove->next;
        node_to_remove->next = NULL;
    }
}

int main() {
	node_t *head = NULL;
	node_t *tmp;
	for (int i = 0; i < 10; i++) {
		tmp = create_new_node(i);
		tmp->next = head;
		head = tmp;
	}
    node_t *new2 = create_new_node(78);
    tmp = insert_at_head(&head, new2);
    node_t *found = find_node(head, 5);
    if (found) printf("Node found with value %d\n", found->value);
    else printf("Node not found\n");
    insert_after_node(found, create_new_node(86));
    remove_node(&head, find_node(head, 9));
	print_list(head);
	return 0;
}
