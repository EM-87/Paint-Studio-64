#include "sound.h"
#include <stdio.h>
#include <string.h>

static bool s_sound_inited= false;

/*
 * Minimal stubs for sound. On real hardware, 
 * would use the Audio Interface (AI) or RSP microcodes for audio playback.
 */

bool sound_init() {
    s_sound_inited= true;
    printf("[Sound] init ok.\n");
    return true;
}

void sound_play_effect(SoundEffect sfx) {
    if(!s_sound_inited) return;
    switch(sfx){
        case SFX_TOOL_SELECT:
            printf("[Sound] sfx=TOOL_SELECT\n");
            break;
        case SFX_DRAW_LINE:
            printf("[Sound] sfx=DRAW_LINE\n");
            break;
        case SFX_FILL_AREA:
            printf("[Sound] sfx=FILL_AREA\n");
            break;
        case SFX_LAYER_SWITCH:
            printf("[Sound] sfx=LAYER_SWITCH\n");
            break;
        default:
            printf("[Sound] sfx=unknown?\n");
            break;
    }
}

void sound_close() {
    if(s_sound_inited){
        printf("[Sound] close.\n");
    }
    s_sound_inited= false;
}
