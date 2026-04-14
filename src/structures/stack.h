/**
 * stack.c
 * definition for generic stack and the functions that act on one
 */

#ifndef __STACK__
#define __STACK__

#include <stdlib.h>

typedef struct {
    void **data;
    void **top;
    size_t capacity;
} Stack;

/**
 * returns a reference to an allocated stack.
 */
Stack *stk_create(size_t capacity);

/**
 * frees all space allocated for the stack.
 *
 * does not deallocate the space given to the items referenced by the stack.
 */
void stk_destroy(Stack *stack);

/**
 * returns the number of items in the given stack.
 */
size_t stk_size(Stack *stack);

/**
 * adds the given item to the top of the given stack.
 */
void stk_push(Stack *stack, void *item);

/**
 * returns a reference to the item on top of the stack.
 */
void *stk_peek(Stack *stack);

/**
 * removes the top item of the stack and returns a reference to it.
 */
void *stk_pop(Stack *stack);

#endif