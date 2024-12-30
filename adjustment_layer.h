#ifndef ADJUSTMENT_LAYER_H
#define ADJUSTMENT_LAYER_H

#include <stdbool.h>

/*
 * Non-destructive adjustment layers for brightness/contrast, etc.
 * We'll do a simple struct that can be toggled on or off and 
 * applied to the final render or to each layer temporarily.
 */

typedef struct {
    float brightness; // range -1.0..+1.0
    float contrast;   // range  0.0..+2.0
    bool active;
} AdjustmentLayer;

/* Initialize with default values (no change). */
void adjustment_init(AdjustmentLayer* al);

/* Set brightness, clamp to [-1..1]. */
void adjustment_set_brightness(AdjustmentLayer* al, float val);

/* Set contrast, clamp to [0..2]. */
void adjustment_set_contrast(AdjustmentLayer* al, float val);

/* Toggle on/off. */
void adjustment_toggle(AdjustmentLayer* al);

/* 
 * Apply to a buffer. If active, modifies the data in memory 
 * or during final compositing. 
 */
void adjustment_apply(const AdjustmentLayer* al, unsigned char* data, int width, int height);

#endif
