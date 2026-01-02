#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>
#include "hash_map.h"

typedef struct Entry {
	int key;
	int value;
	bool used;
} entry;

typedef struct Hash_map {
	entry* entries;
	size_t size;
	size_t count;
} map_t;

static size_t hash(size_t map_size, int key) {
	return ((unsigned int)key) % map_size;
}

map_t* map_init(size_t size) {
	map_t* hmap = malloc(sizeof(map_t));
	hmap->size = size;
	hmap->count = 0;
	hmap->entries = calloc(size, sizeof(entry));
	return hmap;
}

void map_insert(map_t* hm, int key, int val) {
	if (hm->count >= hm->size) return;
	size_t h = hash(hm->size, key);
	// using open addressing with linear probing
	while (hm->entries[h].used) {
		if (hm->entries[h].key == key) {
			hm->entries[h].value = val;
			return;
		}
		h = (h + 1) % hm->size;
	}
	hm->entries[h].value = val;
	hm->entries[h].key = key;
	hm->entries[h].used = true;
	hm->count++;
}

int map_lookup(map_t* hm, int key) {
	size_t h = hash(hm->size, key);
	size_t start = h;
	while (hm->entries[h].used) {
		if (hm->entries[h].key == key)
			return hm->entries[h].value;
		h = (h + 1) % hm->size;
		if (h == start) break;
	}
	return NOT_FOUND;
}

void map_destroy(map_t* hm) {
    free(hm->entries);
    free(hm);
}
