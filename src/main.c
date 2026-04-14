#include "gamelogic/gamelogic.h"
#include "structures/map.h"
#include <stdio.h>
#include <stdlib.h>

extern ConsoleOperator* console_operator;

int hash_int(void* i){
    return *((int*) i);
}

int comp_int(void* i, void* j){
    return *((int*) i) - *((int*) j);
}

void fake_free(){
    return;
}

int main(int argc, char* argv[]){

    Map* m = map_create(4);
    
    

    int a = 1;
    int b = 1;

    map_put(m, &a, hash_int, comp_int, &b);

    

    int c = 2;
    int d = 2;

    map_put(m, &c, hash_int, comp_int, &d);

    int e = 3;
    int f = 3;

    map_put(m, &e, hash_int, comp_int, &f);

    printf("---here---\n");
    
    printf("---here %ld---\n", map_size(m));

    printf("%ld, %ld\n", m->capacity, map_size(m));
    printf("%d, %d\n", c, *((int*) map_get(m, &c, hash_int, comp_int)));

    

    gl_init();

    while(console_operator->console_running){
        char in;
        scanf("%c", &in);
        if (in == 'q') gl_end();
    }

    gl_destroy();
}