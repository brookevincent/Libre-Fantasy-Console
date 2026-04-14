/**
 * implementation for the map structure and its functions
 */

 /**
 * allocates a new map
 */

#include <stdlib.h>
#include <stdio.h>
#include "map.h"

/**
 * allocates a new map
 */
Map* map_create(size_t initial_capacity){
    //initialize map
    Map* m = (Map*) malloc(sizeof(Map));
    m->capacity = initial_capacity;
    //initialize data array
    m->data_array = (LinkedList**) malloc(initial_capacity * sizeof(LinkedList**));

    for(int i = 0; i < initial_capacity; i++){
        m->data_array[i] = NULL;
    }

    return m;
}

/**
 * puts a new element data into the map with the given key or updates it if the element
 * with the given key already exists
 */
void map_put(Map* m, void* key, int (*hashfunc)(void*), int (*keycompfunc)(void*, void*), void* data){
    //put in key value pair
    //get index to insert
    int idx_to_insert = hashfunc(key);
    if(idx_to_insert < 0) idx_to_insert *= -1;
    idx_to_insert = idx_to_insert % m->capacity;
    //insert
    LinkedList* position_to_insert = m->data_array[idx_to_insert];
    
    //position is null case
    if (position_to_insert == NULL){
        position_to_insert = ll_create();
        KeyValuePair* kvp = (KeyValuePair*) malloc(sizeof(KeyValuePair));
        kvp->key = key;
        kvp->value = data;
        ll_push(position_to_insert, kvp);
        m->data_array[idx_to_insert] = position_to_insert;
        m->num_elements++;
    }
    else {
        Node* cur = position_to_insert->head;
        while(cur != NULL){
            if(keycompfunc(key, ((KeyValuePair*) cur->data)->key) == 0){
                cur->data = data;
                break;
            }
            cur = cur->next;
        }
        
        if(cur == NULL) {
            KeyValuePair* kvp = (KeyValuePair*) malloc(sizeof(KeyValuePair));
            kvp->key = key;
            kvp->value = data;
            ll_push(position_to_insert, kvp);
            m->num_elements++;
        }
    }

    
    //check if map needs to be rearranged
    if(map_size(m) > 6 * m->capacity / 10){
        KeyValuePair** data_entries = map_kvps(m);
        size_t size = map_size(m);
        m->capacity *= 2;
        free(m->data_array);
        m->data_array = (LinkedList**) malloc(sizeof(LinkedList) * m->capacity);

        for(int i = 0; i < size; i++){
            map_put(m, data_entries[i]->key, hashfunc, keycompfunc, data_entries[i]->value);
            m->num_elements--;
        }
    }
}

/**
 * returns the element associated with a given key if it exists, NULL otherwise
 */
void* map_get(Map* m, void* key, int (*hashfunc)(void*), int (*keycompfunc)(void*, void*)){
    int idx_to_search = hashfunc(key);
    if(idx_to_search < 0) idx_to_search *= -1;
    idx_to_search = idx_to_search % m->capacity;
    //search
    LinkedList* position_to_search = m->data_array[idx_to_search];

    if(position_to_search != NULL){
        //search linked list
        Node* cur = position_to_search->head;
        while(cur != NULL){
            if(keycompfunc(key, ((KeyValuePair*) cur->data)->key) == 0){
                return ((KeyValuePair*) cur->data)->value;
            }
            cur = cur->next;
        }
    }

    return NULL;
}

/**
 * removes the element with associated with the given key and returns it, returns NULL
 * if it doesnt exist
 */
void* map_remove(Map* m, void* key, int (*hashfunc)(void*), int (*keycompfunc)(void*, void*), void (*keyfree)(void*)){
    int idx_to_search = hashfunc(key);
    if(idx_to_search < 0) idx_to_search *= -1;
    idx_to_search = idx_to_search % m->capacity;
    //search
    LinkedList* position_to_search = m->data_array[idx_to_search];
    

    if(position_to_search != NULL){
        //search linked list
        Node* cur = position_to_search->head;
        Node* prev = NULL;
        Node* out;

        while(cur != NULL){
            if(keycompfunc(key, ((KeyValuePair*) cur->data)->key) == 0){
                break;
            }

            prev = cur;
            cur = cur->next;
        }

        
        if(cur == NULL) return NULL;

        if(prev == NULL){
            
            out = position_to_search->head;
            position_to_search->head = position_to_search->head->next;
        }
        else{
            out = cur;
            prev->next = cur->next;
        }

        

        void* data = ((KeyValuePair*) out->data)->value;

        keyfree(((KeyValuePair*) out->data)->key);
        free(out);

        position_to_search->size--;
        m->num_elements--;
        return data;
    }

    return NULL;
}

/**
 * returns 1 if the key exists in the map, 0 otherwise
 */
int map_contains_key(Map* m, void* key, int (*hashfunc)(void*), int (*keycompfunc)(void*, void*)){
    int idx_to_search = hashfunc(key);
    if(idx_to_search < 0) idx_to_search *= -1;
    idx_to_search = idx_to_search % m->capacity;
    //search
    LinkedList* position_to_search = m->data_array[idx_to_search];

    if(position_to_search != NULL){
        //search linked list
        Node* cur = position_to_search->head;
        Node* out;

        while(cur != NULL){
            if(keycompfunc(key, ((KeyValuePair*) cur->data)->key) == 0){
                return 1;
            }

            cur = cur->next;
        }
    }

    return 0;
}

/**
 * allocates and returns an array of the keys of the hash map
 */
void** map_keys(Map* m){
    void** out = (void**) malloc(sizeof(void*) * map_size(m));
    int out_idx = 0;
    //iterate over every position in the data array
    for(int i = 0; i < m->capacity; i++){
        if(m->data_array[i] != NULL){
            LinkedList* l = m->data_array[i];
            //iterate over linked list
            Node* current_node = l->head;
            while (current_node != NULL){
                out[out_idx] = ((KeyValuePair*) current_node->data)->key;
                out_idx++;
                current_node = current_node->next;
            }
        }
    }

    return out;
}

/**
 * allocates and returns an array of the values of the hash map
 */
void** map_values(Map* m){
    void** out = (void**) malloc(sizeof(void*) * map_size(m));
    int out_idx = 0;
    //iterate over every position in the data array
    for(int i = 0; i < m->capacity; i++){
        if(m->data_array[i] != NULL){
            LinkedList* l = m->data_array[i];
            //iterate over linked list
            Node* current_node = l->head;
            while (current_node != NULL){
                out[out_idx] = ((KeyValuePair*) current_node->data)->value;
                out_idx++;
                current_node = current_node->next;
            }
        }
    }

    return out;
}

/**
 * allocates and returns an array of references to KeyValuePairs of the hash map
 */
KeyValuePair** map_kvps(Map* m){
    KeyValuePair** out = (KeyValuePair**) malloc(sizeof(KeyValuePair*) * map_size(m));
    int out_idx = 0;
    //iterate over every position in the data array
    for(int i = 0; i < m->capacity; i++){
        if(m->data_array[i] != NULL){
            LinkedList* l = m->data_array[i];
            //iterate over linked list
            Node* current_node = l->head;
            while (current_node != NULL){
                out[out_idx] = current_node->data;
                out_idx++;
                current_node = current_node->next;
            }
        }
    }

    return out;
}

/**
 * returns the size of the hash map
 */
size_t map_size(Map* m){
    return m->num_elements;
}

/**
 * frees all data from the hash map, using the freefunc
 */
void map_clear(Map* m, void (*freefunc)(void *), void (*keyfree)(void*));

/**
 * frees the data associated with the hash map
 */
void map_destroy(Map* m);