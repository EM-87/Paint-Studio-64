#ifndef TRANSFORM_SYSTEM_H
#define TRANSFORM_SYSTEM_H

#include <ultra64.h>
#include <stdbool.h>

/*
 * Additional transformations: flipping horizontally/vertically,
 * skewing, scaling, etc.
 */

bool transform_flip(unsigned char* data, int width, int height, bool horizontal);
bool transform_skew(unsigned char* data, int width, int height, float skewX, float skewY);
bool transform_scale(unsigned char* data, int width, int height, float factor);

#endif
