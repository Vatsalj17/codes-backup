#ifndef MAP_H
#define MAP_H

#include <stddef.h>

#define NOT_FOUND INT_MIN

typedef struct Hash_map map_t;

map_t* map_init(size_t size);
void map_insert(map_t* hm, int key, int val);
int map_lookup(map_t* hm, int key);
int map_delete(map_t* hm, int key);
void map_destroy(map_t* hm);

#endif
