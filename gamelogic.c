/**
 * implements gamelogic.h
 */
#include "gamelogic.h"
#include <stdlib.h>

ConsoleOperator* console_operator;

/**
 * initializes the console operator
 */
void gl_init(){
    console_operator = (ConsoleOperator*) malloc(sizeof(ConsoleOperator));
    console_operator->console_running = 1;
    console_operator->console_paused = 0;
}

/**
 * pauses the console
 */
void gl_pause(){
    console_operator->console_paused = 1;
}

/**
 * unpauses the console
 */
void gl_unpause(){
    console_operator->console_paused = 0;
}

/**
 * turns off the console
 */
void gl_end(){
    console_operator->console_running = 0;
    console_operator->cs = END;
}

/**
 * checks whether the console is running
 */
int gl_is_running(){
    return console_operator->console_running;
}

/**
 * checks whether the console is paused
 */
int gl_is_paused(){
    return console_operator->console_paused;
}

/**
 * destroys the console operator
 */
void gl_destroy(){
    free(console_operator);
}
