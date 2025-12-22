#include "stack.h"
#include "queue.h"
#include <stdio.h>

int main(void) {
    stack_t* s = stack_init(10);
    push(s, 4);
    stack_destroy(s);
    printf("got it\n");
    queue_t* q = queue_init(11);
    queue_destroy(q);
}
