person* hash_table_lookup(char* name) {
	int index = hash(name);
	for (int i = 0; i < TABLE_SIZE; i++) {
		int try = (index + i) % TABLE_SIZE;
		if (hashTable[try] != NULL && strncmp(hashTable[try]->name, name, MAX_NAME) == 0) {
			return hashTable[try];
		}
	}
	return NULL;
}