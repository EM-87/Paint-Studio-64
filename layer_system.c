#include "layer_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void layer_system_init(LayerInfo* info, int layer_count, int layer_size) {
    if(layer_count> MAX_LAYERS) layer_count= MAX_LAYERS;
    info->layer_count= layer_count;
    info->current_layer= 0;
    for(int i=0; i<layer_count; i++){
        info->layers[i].visible= true;
        info->layers[i].opacity= 1.0f;
        info->layers[i].data= (unsigned char*)malloc(layer_size);
        if(info->layers[i].data){
            memset(info->layers[i].data, 0, layer_size);
        }
    }
    for(int i=layer_count; i<MAX_LAYERS; i++){
        info->layers[i].data= NULL;
    }
    printf("[LayerSystem] init with %d layers.\n", layer_count);
}

void toggle_layer_visibility(LayerInfo* info, int layer_index) {
    if(layer_index<0|| layer_index>= info->layer_count) return;
    info->layers[layer_index].visible= !info->layers[layer_index].visible;
    printf("[LayerSystem] layer %d visibility=%d\n", layer_index,
           (int)info->layers[layer_index].visible);
}

void set_layer_opacity(LayerInfo* info, int layer_index, float opacity){
    if(layer_index<0||layer_index>= info->layer_count) return;
    if(opacity<0.0f) opacity=0.0f;
    if(opacity>1.0f) opacity=1.0f;
    info->layers[layer_index].opacity= opacity;
    printf("[LayerSystem] layer %d opacity=%.2f\n", layer_index, opacity);
}

void select_layer(LayerInfo* info, int layer_index){
    if(layer_index<0||layer_index>= info->layer_count) return;
    info->current_layer= layer_index;
    printf("[LayerSystem] current layer=%d\n", layer_index);
}

void render_layers(LayerInfo* info, int layer_size){
    /* stub: in real code, we'd blend each visible layer onto final output */
    printf("[LayerSystem] rendering visible layers...\n");
}

void layer_reorder(LayerInfo* info, int from_index, int to_index){
    if(from_index<0||from_index>= info->layer_count) return;
    if(to_index<0  ||to_index>= info->layer_count) return;
    if(from_index== to_index) return;

    CanvasLayer temp= info->layers[from_index];
    if(from_index< to_index){
        for(int i= from_index; i< to_index; i++){
            info->layers[i]= info->layers[i+1];
        }
        info->layers[to_index]= temp;
    } else {
        for(int i= from_index; i> to_index; i--){
            info->layers[i]= info->layers[i-1];
        }
        info->layers[to_index]= temp;
    }
    printf("[LayerSystem] moved layer %d to %d\n", from_index, to_index);
}
