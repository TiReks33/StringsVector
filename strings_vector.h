#ifndef __STRINGS_VECTOR_PUBLIC__
#define __STRINGS_VECTOR_PUBLIC__


// C


//#include <stddef.h>
#include "Bool.h"


typedef struct strings_vector strings_vector;


// ::'Vector of strings' object implementation (contigious container) with basic functionality as opaque struct's pointer; uses exponential buffer growth.::


// [Public user's interface]

//##################################################################################
// 1) Object condition WILL BE changed trough execution of this 'methods' :
//##################################################################################

// [::Create && init new object::]
// 
// Function will allocate memory and initialize opaque struct's pointer to begin 
// use a 'strings_vector' container object.
// Result by 'return' and/or by argument pointer (address pass); 
// NULL is allowed for argument.
// Need to call 'sv_free' after to destroy new object (deallocate its memory). 
strings_vector * sv_init(strings_vector ** vect__);


// [::Completely dealloc object from memory::]
//
// In result, object's pointer will become 'dangling'! Call 'sv_init' again after to 
// re-initialize pointer and use vector again.
void sv_free(strings_vector * vect__);


// [::Increase (realloc) internal capacity of passed vector to 'n' slots::]
//
// Function will do its job ONLY if 'n' is greater than current vector's internal
// capacity (will do nothing usefull if 'n' is less or equal of current vector's 
// internal capacity). 
// Returns capacity value after operation.
size_t sv_reserve(strings_vector * v, size_t n);


// [::Shrink internal capacity::]
//
// Function will shrink (free) excess internal capacity to current vector's number
// of elements.
void sv_shrink_to_fit(strings_vector * v);


// [::Push back (add element)::]
//
// Add new element to the back of vector; returns vector's size after operation.
size_t sv_push_back(strings_vector * vect__, char const * new_string__);


// [::Pop back (remove element)::]
//
// Remove element from the back of vector; returns vector's size after operation.
size_t sv_pop_back(strings_vector * vect__);


// [::Replace element::]
//
// Replace vector's string element by new string via it's 
// position (index) in vector.
Bool sv_replace_string(strings_vector * psv__, size_t sv_index_to_replace, char const * new_str__);


// [::Remove all elements::]
//
// Remove all current string elements from vector (all container's object current
// memory (included its already allocated 'slots' for strings) will not be 
// touched, and vector will remain valid, in compare to 'sv_free'!). 
void sv_clear(strings_vector * vect__);


// [::Copy "strings_vector"'s content to another "strings_vector"::]
//
// Copy content from vector-'transmitter' (const) to vector-'receiver'
// (new strings elements will be added to existings ones in 'receiver');
// 'receiver' vector will be returned.
// Both objects must be previously initialized via 'sv_init(..)'.
// P.S. "receiver"'s underlying array's 1) slots reallocation (if 
// neccessary) + 2) additional allocations for new strings will 
// be occured.
strings_vector * /*void*/ sv_copy(strings_vector * recv, strings_vector const * transmit);


// [::Move "strings_vector"'s content to another "strings_vector"::]
//
// Move content from vector-'transmitter' (NON-const) to vector-'receiver'
// (new strings elements will be added to existings ones in 'receiver');
// 'receiver' vector will be returned, and "transmitter"'s strings elements 
// pointers will be NULL-ed (but NOT deallocated!). 
// Both objects must be previously initialized via 'sv_init(..)'.
// P.S. only reallocation of underlying "receiver"'s array's slots (if
// neccessary) will be occured.
// P.S.S. "transmitter"'s internal capacity will not be touched for opti-
// mization purposes. Use 'sv_shrink_to_fit(..)' afterwards if necessary.
strings_vector * /*void*/ sv_move(strings_vector * recv, strings_vector * transmit);


// [::Sort vector::]
//
// sort vector (ASCII/Unicode machine sort) in ascending ('order' arg is True) or
// descending ('order' arg is False) order
void sv_sort(strings_vector * v__, Bool order__);



//################################################################################
// 2) Object condition will NOT be changed trough execution of this 'methods' :
//################################################################################

// [::Print content (single line)::]
//
// Print all vector's elements with indexes (single line)
void sv_print(strings_vector const * vect__);


// [::Print content (newlines separate)::]
//
// Print all vector's elements with indexes separated by newlines 
void sv_print_nl(strings_vector const * vect__);


// [::Get size::]
//
// Get current number of elements
size_t sv_size(strings_vector const * vect__);


// [::Get internal capacity::]
//
// Get current number of underlying allocated slots
size_t sv_capacity(strings_vector const * vect__);


// [::Index element access::]
//
// Get vector's element by index
char const * sv_get(strings_vector const * psv__, size_t index__);


// [::Index element access (+bounds check)::]
//
// Get vector's element by index, plus additional check via 'bound' flag
// -- in case of function returns NULL; if 'bound' == True -- you get 
// valid 'NULL' pointer element inside Vector's bounds; otherwise, 
// if 'bound' == False -- provided index is out of bounds.
char const * sv_get_b(strings_vector const * psv__, size_t index__, Bool * bound);


// [::Raw array access (const)::]
//
// Get internal container's constant array of constant strings;
// explicit const type casting needed if you need to modify raw 
// vector's strings or symbols in strings (allowed, because
// dynamicly allocated, NOT const C-'strings' pointers used 
// underlying)
char const * const * sv_data(strings_vector const * vect__);


// [::Empty check::]
//
// check if vector is empty
Bool sv_empty(strings_vector const * v__);


#endif //__STRINGS_VECTOR_PUBLIC__



