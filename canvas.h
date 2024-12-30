#ifndef CANVAS_H
#define CANVAS_H

#include <stdbool.h>

/*
 * Basic definitions for an N64 Paint canvas, e.g., default resolution.
 * This was used in earlier versions to store canvas size or default layers.
 */

#define CANVAS_DEFAULT_WIDTH  320
#define CANVAS_DEFAULT_HEIGHT 240
#define LAYERS_DEFAULT        3

/* 
 * A simple struct might track width/height 
 * if we have a distinct notion of a "canvas."
 */
typedef struct {
    int width;
    int height;
    int layers;
    bool requires_expansion;
} CanvasInfo;

#endif
