#ifndef ADVANCED_FILTERS_H
#define ADVANCED_FILTERS_H

#include <ultra64.h>
#include <stdbool.h>

/*
 * Various filters: sepia, gaussian blur, edge detect, 
 * sharpen, grayscale, plus bucket fill as an extra tool.
 */

typedef enum {
    FILTER_NONE=0,
    FILTER_SEPIA,
    FILTER_GAUSSIAN_BLUR,
    FILTER_EDGE_DETECT,
    FILTER_SHARPEN,
    FILTER_GRAYSCALE
} FilterType;

typedef struct {
    FilterType type;
    float strength; // e.g. how strong the filter is
    bool active;
} FilterSettings;

/* Applies the chosen filter to 8-bit data. */
void filters_apply(const FilterSettings* fs, unsigned char* data, int width, int height);

/* A typical 'bucket fill' approach (flood fill). */
bool bucket_fill(unsigned char* data, int width, int height, int x, int y, unsigned char new_color);

#endif
