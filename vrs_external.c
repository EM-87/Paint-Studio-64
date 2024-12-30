#include "vrs_external.h"
#include <stdio.h>
#include <string.h>

static bool s_vr_inited= false;
static char s_last_command[32];

/*
 * A minimal stub that pretends to handle external VR.
 */

bool external_vr_init() {
    printf("[ExtVR] Initializing external VR system.\n");
    s_vr_inited= true;
    s_last_command[0]= '\0';
    return true;
}

bool external_vr_configure(int sample_rate, const char* dictionary_path) {
    if(!s_vr_inited) return false;
    printf("[ExtVR] sample_rate=%d, dictionary=%s\n", sample_rate, dictionary_path);
    return true;
}

void on_voice_data(const int16_t* samples, int count) {
    if(!s_vr_inited) return;
    if(count>0){
        // Simulate detection of an external command
        strcpy(s_last_command,"EXT_CMD");
    }
}

const char* external_vr_get_command() {
    if(!s_vr_inited) return NULL;
    if(s_last_command[0]){
        return s_last_command;
    }
    return NULL;
}

void external_vr_shutdown() {
    if(s_vr_inited){
        printf("[ExtVR] Shutting down external VR.\n");
    }
    s_vr_inited= false;
}
