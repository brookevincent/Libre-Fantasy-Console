/**
 * map.h
 * defines necessary structures and functions for a hashmap
 */

#ifndef __MAP__
#define __MAP__

#include "linkedlist.h"

/**
 * structure for a key value pair
 */
typedef struct KeyValuePair {
    /**
     * the key
     */
    void* key;
    /**
     * the value associated with the key
     */
    void* value;
} KeyValuePair;

/**
 * structure for a hashmap
 */
typedef struct Map {
    /**
     * array that holds map data
     */
    LinkedList** data_array;
    /**
     * current capacity of the map
     */
    int capacity;
    /**
     * current number of elements of the map
     */
    int num_elements;
} Map;

/**
 * allocates a new map
 */
Map* map_create(int initial_capacity);

/**
 * puts a new element data into the map with the given key or updates it if the element
 * with the given key already exists
 */
void map_put(Map* m, void* key, int (*hashfunc)(void*), int (*keycompfunc)(void*, void*), void* data);

/**
 * returns the element associated with a given key if it exists, NULL otherwise
 */
void* map_get(Map* m, void* key, int (*hashfunc)(void*), int (*keycompfunc)(void*, void*));

/**
 * removes the element with associated with the given key and returns it, returns NULL
 * if it doesnt exist
 */
void* map_remove(Map* m, void* key, int (*hashfunc)(void*), int (*keycompfunc)(void*, void*));

/**
 * returns 1 if the key exists in the map
 */
int map_contains_key(Map* m, void* key, int (*keycompfunc)(void*, void*));

/**
 * allocates and returns an array of the keys of the hash map
 */
void** map_keys(Map* m);

/**
 * allocates and returns an array of the values of the hash map
 */
void** map_values(Map* m);

/**
 * allocates and returns an array of references to KeyValuePairs of the hash map
 */
KeyValuePair** map_kvps(Map* m);

/**
 * returns the size of the hash map
 */
int map_size(Map* m);

/**
 * frees all data from the hash map, using the freefunc
 */
void map_clear(Map* m, void (*freefunc)(void *));

/**
 * frees the data associated with the hash map
 */
void map_destroy(Map* m);

#endif