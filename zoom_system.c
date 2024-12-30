#include "zoom_system.h"
#include <stdio.h>

static float s_zoom_factor= 1.0f;

void zoom_system_init(){
    s_zoom_factor= 1.0f;
    printf("[ZoomSystem] init factor=1.0\n");
}

void zoom_in(){
    s_zoom_factor+= 0.1f;
    if(s_zoom_factor>4.0f) s_zoom_factor=4.0f;
    printf("[ZoomSystem] zoom in -> %.2f\n", s_zoom_factor);
}

void zoom_out(){
    s_zoom_factor-= 0.1f;
    if(s_zoom_factor<0.1f) s_zoom_factor=0.1f;
    printf("[ZoomSystem] zoom out -> %.2f\n", s_zoom_factor);
}

float zoom_get_factor(){
    return s_zoom_factor;
}
