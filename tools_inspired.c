#include "tools_inspired.h"
#include <stdio.h>
#include <string.h>

/*
 * Implementation stubs for game-inspired painting tools.
 */

void tool_splatoon(LayerInfo* info, int x, int y, int size){
    if(info->current_layer<0 || info->current_layer>= info->layer_count) return;
    CanvasLayer* layer= &info->layers[ info->current_layer ];
    if(!layer->data) return;

    printf("[ToolsInspired] Splatoon at layer %d, coords=(%d,%d), size=%d\n",
           info->current_layer, x,y, size);
    // e.g. fill a circle region with "ink color"
}

void tool_mario_paint_stamp(LayerInfo* info, int x, int y, int stamp_id){
    if(info->current_layer<0 || info->current_layer>= info->layer_count) return;
    CanvasLayer* layer= &info->layers[ info->current_layer ];
    if(!layer->data) return;

    printf("[ToolsInspired] Mario Paint stamp ID=%d at layer %d coords=(%d,%d)\n",
           stamp_id, info->current_layer, x,y);
    // e.g. copy some stamp pattern onto layer->data
}
