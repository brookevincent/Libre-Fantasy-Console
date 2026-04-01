/**
 * stack.c
 * implementation of a generic c stack
 */

#include "stack.h"

/**
 * returns a reference to an allocated stack.
 */
Stack *stk_create(int capacity){
    Stack* s = (Stack*) malloc(sizeof(Stack));
    s->data = (void**) malloc(sizeof(void**) * capacity);
    s->top = s->data;
    s->capacity = capacity;

    return s;
}

/**
 * frees all space allocated for the stack.
 *
 * does not deallocate the space given to the items referenced by the stack.
 */
void stk_destroy(Stack *stack){
    free(stack->data);
    free(stack);
}

/**
 * returns the number of items in the given stack.
 */
int stk_size(Stack *stack){
    return (int) (stack->top - stack->data);
}

/**
 * adds the given item to the top of the given stack.
 */
void stk_push(Stack *stack, void *item){
    *(stack->top) = item;
    stack->top++;

    //allocate more memory to stack
    if (stack->top > stack->data + stack->capacity){
        int new_capacity = 2 * stack->capacity;
        void** old_data = stack->data;
        stack->data = (void**) malloc(sizeof(void**) * new_capacity);
        //copy data over
        void** temp_ptr = old_data;
        int i = 0;
        while(temp_ptr < old_data + stack->capacity){
            stack->data[i] = temp_ptr;
            i++;
            temp_ptr++;
        }

        stack->top = stack->data + new_capacity;

        //free old data storage
        free(old_data);

        stack->capacity = new_capacity;
    }
}

/**
 * returns a reference to the item on top of the stack.
 */
void *stk_peek(Stack *stack){
    return *(stack->top - 1);
}

/**
 * removes the top item of the stack and returns a reference to it.
 */
void *stk_pop(Stack *stack){
    void* out = *(stack->top - 1);
    stack->top--;
    return out;
}