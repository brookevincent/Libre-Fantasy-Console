/**
 * defines ConsoleOperator struct and operations that go with it
 */
#ifndef __GAMELOGIC__
#define __GAMELOGIC__

enum CONSOLE_STATE {
    INITIALIZATION = 1,
    MAIN_MENU = 2,
    GAME = 3,
    END = 4
};

typedef struct ConsoleOperator{
    /**
     * determines whether or not the game is running
     */
    int console_running;
    /**
     * determines whether or not the game is paused
     */
    int console_paused;
    /**
     * the current state of the console
     */
    enum CONSOLE_STATE cs;
} ConsoleOperator;


/**
 * initializes the console operator
 */
void gl_init();

/**
 * pauses the console
 */
void gl_pause();

/**
 * unpauses the console
 */
void gl_unpause();

/**
 * turns off the console
 */
void gl_end();

/**
 * checks whether the console is running
 */
int gl_is_running();

/**
 * checks whether the console is paused
 */
int gl_is_paused();

/**
 * destroys the console operator
 */
void gl_destroy();

#endif