#ifndef BRUSH_SYSTEM_H
#define BRUSH_SYSTEM_H

#include <ultra64.h>
#include <stdbool.h>

#define MAX_CUSTOM_BRUSHES 8
#define BRUSH_NAME_LEN     16

/*
 * Allows creating custom brushes, storing them, 
 * and loading them from the Controller Pak.
 */

typedef struct {
    char   name[BRUSH_NAME_LEN];
    int    width;
    int    height;
    bool   use_opacity;
    unsigned char* data;
} CustomBrush;

typedef struct {
    CustomBrush brushes[MAX_CUSTOM_BRUSHES];
    int brush_count;
} BrushCollection;

void brush_system_init(BrushCollection* bc);
bool brush_create(BrushCollection* bc, const char* name, int w, int h, bool use_opacity);
bool brush_save_collection(const BrushCollection* bc);
bool brush_load_collection(BrushCollection* bc);

/* Apply a custom brush to a layer at (x,y). */
void brush_apply(const CustomBrush* brush, unsigned char* layer_data,
                 int layer_width, int layer_height, int x, int y);

#endif
