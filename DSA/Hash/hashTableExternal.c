#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct person {
	char name[MAX_NAME];
	int age;
	struct person* next;
} person;

person* hashTable[TABLE_SIZE];

unsigned int hash(char* name) {
	int length = strnlen(name, MAX_NAME);
	unsigned int hash_value = 0;
	for (int i = 0; i < length; i++) {
		hash_value += name[i];
		hash_value = (hash_value * name[i]) % TABLE_SIZE;
	}
	return hash_value;
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
			person* temp = hashTable[i];
			while (temp != NULL) {
				printf("%s -> ", temp->name);
				temp = temp->next;
			}
			printf("\n");
		}
	}
	printf("\t-----END-----\n\n");
}

bool hash_table_insert(person* p) {
	if (p == NULL) return false;
	int index = hash(p->name);
	p->next = hashTable[index];
	hashTable[index] = p;
	return true;
}

person* hash_table_lookup(char* name) {
	int index = hash(name);
	person* temp = hashTable[index];
	while (temp != NULL && strncmp(temp->name, name, MAX_NAME) != 0)
		temp = temp->next;
	return temp;
}

person* hash_table_delete(char* name) {
	int index = hash(name);
	person* temp = hashTable[index];
	person* prev = NULL;
	while (temp != NULL && strncmp(temp->name, name, MAX_NAME) != 0) {
		prev = temp;
		temp = temp->next;
	}
	if (temp == NULL) return NULL;
	if (prev == NULL)
		hashTable[index] = temp->next;	// deleting the head
	else
		prev->next = temp->next;
	return temp;
}

int main(void) {
	init_hash_table();

	person jacob = {.name = "Jacob", .age = 256};
	person kate = {.name = "Kate", .age = 27};
	person mpho = {.name = "Mpho", .age = 14};
	person sarah = {.name = "Sarah", .age = 54};
	person edna = {.name = "Edna", .age = 15};
	person maren = {.name = "Maren", .age = 25};
	person eliza = {.name = "Eliza", .age = 34};
	person robert = {.name = "Robert", .age = 1};
	person jane = {.name = "Jane", .age = 75};
	hash_table_insert(&jacob);
	hash_table_insert(&kate);
	hash_table_insert(&mpho);
	hash_table_insert(&sarah);
	hash_table_insert(&edna);
	hash_table_insert(&maren);
	hash_table_insert(&eliza);
	hash_table_insert(&robert);
	hash_table_insert(&jane);

	hash_table_delete("Mpho");
	print_table();

	// lookup
	char* names[] = {"Jacob", "George", "Mpho", "Maren", "Robert", NULL};
	for (int i = 0; names[i] != NULL; i++) {
		person* tmp = hash_table_lookup(names[i]);
		if (tmp == NULL)
			printf("%s not found\n", names[i]);
		else
			printf("Found %s\n", tmp->name);
	}

	/* printf("Jacob => %u\n", hash("Jacob"));
	printf("Natalie => %u\n", hash("Natalie"));
	printf("Sara => %u\n", hash("Sara"));
	printf("Mpho => %u\n", hash("Mpho"));
	printf("Tebogo => %u\n", hash("Tebogo"));
	printf("Ron => %u\n", hash("Ron"));
	printf("Jane => %u\n", hash("Jane"));
	printf("Maren => %u\n", hash("Maren"));
	printf("Bill => %u\n", hash("Bill")); */
}
