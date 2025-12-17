#include <stdio.h>
#include "object.h"

int main() {
    object_t* int_a = new_integer(10);
    object_t* int_b = new_integer(20);
    object_t* int_c = add(int_a, int_b);
    printf("Integer addition: %d\n", int_c->data.v_int);

    object_t* float_a = new_float(15.5f);
    object_t* float_b = add(int_a, float_a);
    printf("Integer and float addition: %f\n", float_b->data.v_float);

    object_t* str_a = new_string("Hello, ");
    object_t* str_b = new_string("World!");
    object_t* str_c = add(str_a, str_b);
    printf("String concatenation: %s\n", str_c->data.v_string);
    printf("String length: %d\n", length(str_c));

    object_t* vec_a = new_vector3(new_integer(1), new_integer(2), new_integer(3));
    object_t* vec_b = new_vector3(new_integer(4), new_integer(5), new_integer(6));
    object_t* vec_c = add(vec_a, vec_b);
    printf("Vector addition: (%d, %d, %d)\n",
           vec_c->data.v_vector3.x->data.v_int,
           vec_c->data.v_vector3.y->data.v_int,
           vec_c->data.v_vector3.z->data.v_int);

    object_t* arr_a = new_array(2);
    array_set(arr_a, 0, new_integer(100));
    array_set(arr_a, 1, new_integer(200));

    object_t* arr_b = new_array(3);
    array_set(arr_b, 0, new_integer(300));
    array_set(arr_b, 1, new_integer(400));
    array_set(arr_b, 2, new_integer(500));

    object_t* arr_c = add(arr_a, arr_b);
    printf("Array concatenation length: %d\n", length(arr_c));
    for (int i = 0; i < length(arr_c); i++) {
        object_t* element = array_get(arr_c, i);
        printf("Array element %d: %d\n", i, element->data.v_int);
    }

    return 0;
}
