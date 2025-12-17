#include <stdio.h>
#include <unistd.h>

int main(void) {
	void* first = sbrk(0);
	void* second = sbrk(0x89);
	void* third = sbrk(0);
    printf("First: %p\n", first); 
    printf("Second: %p\n", second); 
    printf("Third: %p\n", third); 
}
