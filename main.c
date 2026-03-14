#include "gamelogic/gamelogic.h"
#include <stdio.h>

extern ConsoleOperator* console_operator;

int main(int argc, char* argv[]){
    gl_init();

    while(console_operator->console_running){
        char in;
        scanf("%c", &in);
        if (in == 'q') gl_end();
    }

    gl_destroy();
}