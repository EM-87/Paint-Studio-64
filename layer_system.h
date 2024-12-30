#ifndef LAYER_SYSTEM_H
#define LAYER_SYSTEM_H

#include <stdbool.h>

#define MAX_LAYERS 6

typedef struct {
    bool visible;
    float opacity;
    unsigned char* data;
} CanvasLayer;

typedef struct {
    CanvasLayer layers[MAX_LAYERS];
    int current_layer;
    int layer_count;
} LayerInfo;

void layer_system_init(LayerInfo* info, int layer_count, int layer_size);
void toggle_layer_visibility(LayerInfo* info, int layer_index);
void set_layer_opacity(LayerInfo* info, int layer_index, float opacity);
void select_layer(LayerInfo* info, int layer_index);
void render_layers(LayerInfo* info, int layer_size);
void layer_reorder(LayerInfo* info, int from_index, int to_index);

#endif
