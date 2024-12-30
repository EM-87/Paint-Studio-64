#include "multiplayer_competitions.h"
#include <stdio.h>
#include <time.h>

static bool s_competition_active= false;
static time_t s_start_time;
static int s_duration= 30; // seconds

void competition_mode_init(){
    s_competition_active= true;
    s_start_time= time(NULL);
    printf("[Competition] Mode started, duration=%d sec.\n", s_duration);
}

void competition_update(PlayerInfo* players, int player_count){
    if(!s_competition_active) return;
    time_t now= time(NULL);
    if((int)difftime(now, s_start_time)>= s_duration){
        s_competition_active= false;
        printf("[Competition] Time's up!\n");
        // Could evaluate who "won"
    }
}

bool competition_is_finished(){
    return !s_competition_active;
}
