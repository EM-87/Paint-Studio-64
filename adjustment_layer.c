#include "adjustment_layer.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void adjustment_init(AdjustmentLayer* al){
    al->brightness= 0.0f;
    al->contrast= 1.0f;
    al->active= false;
    printf("[AdjustmentLayer] init.\n");
}

void adjustment_set_brightness(AdjustmentLayer* al, float val){
    if(val< -1.0f) val= -1.0f;
    if(val>  1.0f) val=  1.0f;
    al->brightness= val;
    printf("[AdjustmentLayer] brightness=%.2f\n", val);
}

void adjustment_set_contrast(AdjustmentLayer* al, float val){
    if(val< 0.0f) val= 0.0f;
    if(val> 2.0f) val= 2.0f;
    al->contrast= val;
    printf("[AdjustmentLayer] contrast=%.2f\n", val);
}

void adjustment_toggle(AdjustmentLayer* al){
    al->active= !al->active;
    printf("[AdjustmentLayer] active=%d\n", (int)al->active);
}

void adjustment_apply(const AdjustmentLayer* al, unsigned char* data, int width, int height){
    if(!al->active) return;
    // For demonstration, assume data is grayscale 0..255
    // brightness shifts up or down, contrast expands around 0.5
    int size= width*height;
    float br= al->brightness; // -1..1
    float ct= al->contrast;   // 0..2

    for(int i=0;i<size;i++){
        float pix= data[i]/255.0f;
        // apply contrast around 0.5
        pix= (pix - 0.5f)* ct + 0.5f;
        pix+= br; 
        if(pix<0.0f) pix=0.0f;
        if(pix>1.0f) pix=1.0f;
        data[i]= (unsigned char)(pix*255.0f+0.5f);
    }
    printf("[AdjustmentLayer] applied brightness=%.2f contrast=%.2f\n", br, ct);
}
