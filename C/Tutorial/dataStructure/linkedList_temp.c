#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int value;
	struct node* next;
} node_t;

int list_size(node_t* head) {
	int i = 0;
	node_t* temp = head;
	while (temp != NULL) {
		temp = temp->next;
		i++;
	}
	return i;
}

void print_list(node_t* head) {
	node_t* temp = head;
	while (temp != NULL) {
		printf("%d, ", temp->value);
		temp = temp->next;
	}
	printf("\n");
}

node_t* create_new_node(int value) {
	node_t* result = (node_t*)malloc(sizeof(node_t));
	result->value = value;
	result->next = NULL;
	return result;
}

node_t* insert_at_head(node_t** head, node_t* node_to_insert) {
	node_to_insert->next = *head;
	*head = node_to_insert;
	return node_to_insert;
}

node_t* find_node(node_t* head, int val) {
	int index = 0;
	node_t* tmp = head;
	while (tmp != NULL) {
		if (tmp->value == val) {
			printf("Node found at %d index\n", index);
			return tmp;
		}
		tmp = tmp->next;
		index++;
	}
	return NULL;
}

void insert_after_node(node_t* node_to_insert_after, node_t* newnode) {
	newnode->next = node_to_insert_after->next;
	node_to_insert_after->next = newnode;
}

void remove_node(node_t** head, node_t* node_to_remove) {
	if (*head == node_to_remove) {
		*head = node_to_remove->next;
		return;
	} else {
		node_t* temp = *head;
		while (temp != NULL && temp->next != node_to_remove) {
			temp = temp->next;
		}
		if (temp == NULL) return;
		temp->next = node_to_remove->next;
		node_to_remove->next = NULL;
	}
}

node_t* middle_element(node_t* head) {
	int len = list_size(head);
	node_t* temp = head;
	for (int i = 0; i < len / 2; i++) temp = temp->next;
	return temp;
}

void remove_duplicates(node_t** head) {
	node_t* temp = *head;
	if (temp == NULL) return;
	while (temp->next != NULL) {
		if (temp->value == temp->next->value) {
			remove_node(head, temp);
		}
		if (temp->next == NULL) break;
		temp = temp->next;
	}
}

node_t* reverse_list(node_t* head) {
	if (head == NULL) return NULL;
	node_t* temp = head;
	node_t* rhead = NULL;
	node_t* tail = rhead;
	while (temp != NULL) {
		node_t* r = create_new_node(temp->value);
		if (tail == NULL) {
			rhead = r;
			tail = r;
		} else {
			insert_at_head(&rhead, r);
		}
		temp = temp->next;
	}
	return rhead;
}

int main() {
	node_t* head = NULL;
	node_t* tail = head;
	node_t* tmp;
	int length;
	printf("Enter length of the list: ");
	scanf("%d", &length);
	printf("Enter the values: ");
	for (int i = 0; i < length; i++) {
		int val;
		scanf("%d", &val);
		tmp = create_new_node(val);
		if (tail == NULL) {
			tail = tmp;
			head = tmp;
		} else {
			tail->next = tmp;
			tail = tmp;
		}
	}
	// node_t *new2 = create_new_node(78);
	// tmp = insert_at_head(&head, new2);
	// node_t *found = find_node(head, 5);
	// if (found) printf("Node found with value %d\n", found->value);
	// else printf("Node not found\n");
	// insert_after_node(found, create_new_node(86));
	// remove_node(&head, find_node(head, 9));
	printf("List: ");
	print_list(head);
	remove_duplicates(&head);
	printf("After removing duplicates: ");
	print_list(head);
	node_t* mid = middle_element(head);
	printf("Middle element: %d\n", mid->value);
	printf("Reverse List: ");
	print_list(reverse_list(head));
	return 0;
}
