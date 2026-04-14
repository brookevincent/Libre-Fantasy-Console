/**
 * implementation for the console memory class
 */

#include "conmem.h"
#include <stdlib.h>

MemHandler* conmem_handler;

/**
 * initializes the memory handler for the console
 */
void conmem_init();

/**
 * allocates new memory to the console memory, setting all bytes to zero
 */
void conmem_alloc(void** pointer, size_t size);

/**
 * deallocates a pointer
 */
void conmem_free(void* pointer);

/**
 * associates a pointer with a new pointer
 */
void conmem_assoc(void** pointer, void* to_point_to);

/**
 * deassociate a pointer from its target, sets the pointer to NULL
 */
void conmem_dessoc(void** pointer);

/**
 * cleans any memory units that have no references
 */
void conmem_clean();

/**
 * destroy the memory handler
 */
void conmem_destroy();