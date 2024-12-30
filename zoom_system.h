#ifndef ZOOM_SYSTEM_H
#define ZOOM_SYSTEM_H

#include <ultra64.h>
#include <stdbool.h>

/*
 * Manages a zoom factor (1.0 by default),
 * allowing the user to zoom in/out for precision drawing.
 */

void zoom_system_init();
void zoom_in();
void zoom_out();
float zoom_get_factor();

#endif
