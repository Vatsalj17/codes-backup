#include "heap.h"

#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

typedef char ALIGN[16];

typedef union Header {
	struct {
		size_t size;
		bool is_freed;
		union Header* next;
	} s;
	ALIGN stub;
} header_t;

header_t *head, *tail;
pthread_mutex_t global_lock;

static header_t* get_free_block(size_t size) {
	header_t* curr = head;
	while (curr) {
		if (curr->s.is_freed && curr->s.size >= size)
			return curr;
		curr = curr->s.next;
	}
	return NULL;
}

void* malloc(size_t size) {
	if (!size) return NULL;
	void* block;
	header_t* header;
	pthread_mutex_lock(&global_lock);
	header = get_free_block(size);
	if (header) {
		header->s.is_freed = false;
		pthread_mutex_unlock(&global_lock);
		return (void*)(header + 1);
	}
	size_t total_size = sizeof(header_t) + size;
	block = sbrk(total_size);
	if (block == (void*)-1) {
		pthread_mutex_unlock(&global_lock);
		return NULL;
	}
	header = block;
	header->s.size = size;
	header->s.is_freed = false;
	header->s.next = NULL;
	if (!head)
		head = header;
	if (tail)
		tail->s.next = header;
	tail = header;
	pthread_mutex_unlock(&global_lock);
	return (void*)(header + 1);
}

void free(void* block) {
	if (!block) return;
	header_t *header, *temp;
	void* programbreak;
	pthread_mutex_lock(&global_lock);
	header = (header_t*)block - 1;
	programbreak = sbrk(0);
	if ((char*)block + header->s.size == programbreak) {
		if (head == tail) {
			head = tail = NULL;
		} else {
			temp = head;
			while (temp) {
				if (temp->s.next == tail) {
					temp->s.next = NULL;
					tail = temp;
				}
				temp = temp->s.next;
			}
		}
		sbrk(0 - sizeof(header_t) - header->s.size);
		pthread_mutex_unlock(&global_lock);
		return;
	}
	header->s.is_freed = true;
	pthread_mutex_unlock(&global_lock);
}

void* calloc(size_t n, size_t size) {
	if (!n || !size) return NULL;
	size_t nsize = n * size;
	// check multiplication overflow
	if (size != nsize / n) return NULL;
	void* block = malloc(nsize);
	if (!block) return NULL;
	memset(block, 0, nsize);
	return block;
}

void* realloc(void* block, size_t size) {
	if (!block || !size) return malloc(size);
	header_t* header = (header_t*)block - 1;
    if (header->s.size >= size) return block;
    void* ret = malloc(size);
    if (ret) {
        memcpy(ret, block, header->s.size);
        free(block);
    }
    return ret;
}
