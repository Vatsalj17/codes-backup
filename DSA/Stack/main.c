#include "stack.h"

int main(void) {
    stack_t* s = stack_init(10);
    push(s, 78);
}
