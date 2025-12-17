#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define HEAP_CAPACITY 64000000
#define CHUNK_LIST_CAPACITY 1000

typedef struct {
	void* ptr;
	size_t size;
} Chunk;

typedef struct {
	size_t count;
	Chunk chunks[CHUNK_LIST_CAPACITY];
} ChunkList;

int heap[HEAP_CAPACITY] = {0};
// size_t heap_size = 0;

ChunkList allocedChunks = {0};
ChunkList freeChunks = {
	.count = 1,
	.chunks = {
		[0] = {.ptr = heap, .size = sizeof(heap)},
	},
};
ChunkList tempChunks = {0};

void chunk_list_insert(ChunkList* list, void* ptr, size_t size) {
	assert(list->count < CHUNK_LIST_CAPACITY);
	list->chunks[list->count].ptr = ptr;
	list->chunks[list->count].size = size;
	for (size_t i = list->count; i > 0 && list->chunks[i].ptr < list->chunks[i - 1].ptr; i--) {
		Chunk temp = list->chunks[i];
		list->chunks[i] = list->chunks[i - 1];
		list->chunks[i - 1] = temp;
	}
	list->count++;
}

void chunk_list_remove(ChunkList* list, size_t index) {
	assert(index < list->count);
	for (size_t i = index; i < list->count - 1; i++) {
		list->chunks[i] = list->chunks[i + 1];
	}
	list->count -= 1;
}

void chunk_list_merge(ChunkList* dst, const ChunkList* src) {
	dst->count = 0;
	for (size_t i = 0; i < src->count; i++) {
		const Chunk chunk = src->chunks[i];
		if (dst->count > 0) {
			Chunk* top_chunk = &dst->chunks[dst->count - 1];
			if (top_chunk->ptr + top_chunk->size == chunk.ptr) {
				top_chunk->size += chunk.size;
			} else {
				chunk_list_insert(dst, chunk.ptr, chunk.size);
			}
		} else {
			chunk_list_insert(dst, chunk.ptr, chunk.size);
		}
	}
}

void dump(const ChunkList* list) {
	printf("Chunks(%zu):\n", list->count);
	for (size_t i = 0; i < list->count; i++) {
		printf(" start: %p, size: %zu\n", list->chunks[i].ptr, list->chunks[i].size);
	}
}

int chunk_list_find(const ChunkList* list, void* ptr) {
	for (size_t i = 0; i < list->count; i++) {
		if (list->chunks[i].ptr == ptr) {
			return i;
		}
	}
	return -1;
}

void* h_alloc(size_t size) {
	if (size <= 0) return NULL;
	chunk_list_merge(&tempChunks, &freeChunks);
	freeChunks = tempChunks;
	for (size_t i = 0; i < freeChunks.count; i++) {
		Chunk chunk = freeChunks.chunks[i];
		if (chunk.size >= size) {
			chunk_list_remove(&freeChunks, i);
			void* ptr = chunk.ptr;
			size_t tail_size = chunk.size - size;
			chunk_list_insert(&allocedChunks, chunk.ptr, size);
			if (tail_size > 0) {
				chunk_list_insert(&freeChunks, chunk.ptr + size, tail_size);
			}
			return ptr;
		}
	}
	return NULL;
}

void h_free(void* ptr) {
	if (ptr == NULL) return;
	int index = chunk_list_find(&allocedChunks, ptr);
	assert(index >= 0);
	chunk_list_insert(&freeChunks, allocedChunks.chunks[index].ptr, allocedChunks.chunks[index].size);
	chunk_list_remove(&allocedChunks, index);
}

int main(void) {
	for (int i = 0; i < 10; i++) {
		void* ptr = h_alloc(i);
		if (i % 2 == 0) h_free(ptr);
	}
	// char *root = h_alloc(26);
	// for (int i = 0; i < 26; i++) {
	//     root[i] = 'A' + i;
	// }
	printf("Alloced ");
	dump(&allocedChunks);
	printf("Free ");
	dump(&freeChunks);
}
