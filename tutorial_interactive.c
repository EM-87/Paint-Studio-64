#include "tutorial_interactive.h"
#include <stdio.h>

static int s_step=0;
static bool s_done=false;

void tutorial_init(){
    s_step=0;
    s_done=false;
    printf("[Tutorial] begun.\n");
}

void tutorial_next_step(){
    if(s_done) return;
    s_step++;
    switch(s_step){
        case 1: printf("[Tutorial] Step1: select a layer.\n"); break;
        case 2: printf("[Tutorial] Step2: use a brush.\n"); break;
        case 3: printf("[Tutorial] Step3: apply a filter.\n"); break;
        default:
            printf("[Tutorial] completed!\n");
            s_done= true;
            break;
    }
}

bool tutorial_is_done(){
    return s_done;
}
