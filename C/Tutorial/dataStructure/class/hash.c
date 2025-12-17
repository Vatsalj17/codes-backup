#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 9

typedef struct slots {
    int val;
	struct slots* next;
} slots;

slots* hashTable[TABLE_SIZE];

int hash(int value) {
    return value % 9;
}

void init_hash_table() {
	for (int i = 0; i < TABLE_SIZE; i++) hashTable[i] = NULL;
}

void print_table() {
	for (int i = 0; i < TABLE_SIZE; i++) {
		if (hashTable[i] == NULL) {
			printf("\t%i\t---\n", i);
		} else {
			printf("\t%i\t", i);
			slots* temp = hashTable[i];
			while (temp != NULL) {
				printf("%d -> ", temp->val);
				temp = temp->next;
			}
			printf("\n");
		}
	}
	printf("\t-----END-----\n\n");
}

bool hash_table_insert(slots* s) {
    if(s == NULL) {
        printf("can't insert\n");
        return false;
    }
	int index = hash(s->val);
	s->next = hashTable[index];
	hashTable[index] = s;
	return true;
}

slots* hash_table_lookup(int value) {
	int index = hash(value);
	slots* temp = hashTable[index];
	while (temp != NULL && value == temp->val)
		temp = temp->next;
	return temp;
}

slots* hash_table_delete(int value) {
	int index = hash(value);
	slots* temp = hashTable[index];
	slots* prev = NULL;
	while (temp != NULL && temp->val == value) {
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL) return NULL;
	if (prev == NULL)
		hashTable[index] = temp->next;
	else
		prev->next = temp->next;
	return temp;
}

int main(void) {
	init_hash_table();
    int n, val;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("Enter the values: ");
    for (int i = 0; i < n; i++) {
        scanf(" %d", &val);
        slots* s = malloc(sizeof(slots));
        s->val = val;
        s->next = NULL;
        printf("inserting %d\n", s->val);
        hash_table_insert(s);
        free(s);
    }
    print_table();
}
