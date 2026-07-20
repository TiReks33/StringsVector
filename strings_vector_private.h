#ifndef __STRINGS_VECTOR_PRIVATE__
#define __STRINGS_VECTOR_PRIVATE__


#include <stddef.h>
#include "Bool.h"

// opaque struct ('private' body of object)
struct strings_vector{
    char ** arr_;
    size_t size_, alloc_capacity_; // size_ -- current vector size(how much strings already added to vector), alloc_capacity_ -- how much space ('slots for strings add without realloc') currently allocated;
};

// main function for 'sugar' stdout printing
void sv_print_p(struct strings_vector const * vect__, Bool newline);

// comparator for sort in ascending order
int sv_ascii_order_compar( const void *c_str_p1, const void *c_str_p2);

// comparator for sort in descending order
int sv_ascii_order_compar_desc( const void *c_str_p1, const void *c_str_p2);


#endif //__STRINGS_VECTOR_PRIVATE__



