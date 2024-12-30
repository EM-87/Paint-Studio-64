#include "voice_advanced.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static bool s_adv_inited= false;

bool voice_adv_init(){
    s_adv_inited= true;
    printf("[VoiceAdv] init.\n");
    return true;
}

void voice_adv_shutdown(){
    if(s_adv_inited){
        printf("[VoiceAdv] shutdown.\n");
    }
    s_adv_inited= false;
}

/*
 * Example: parse a full sentence for command keywords. 
 */
const char* voice_adv_process_sentence(const char* sentence){
    if(!s_adv_inited) return NULL;
    if(strstr(sentence,"please set brush")){
        return "BRUSH_CREATE";
    }
    else if(strstr(sentence,"apply filter")){
        return "TOGGLE_ADJUST";
    }
    printf("[VoiceAdv] unrecognized in: '%s'\n", sentence);
    return NULL;
}
