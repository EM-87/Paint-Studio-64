#include "artistic_styles.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

/*
 * Implementation stubs for style transformations. 
 * Each style is basically a specialized color or shape transform.
 */

void style_apply(const ArtStyleSettings* st, unsigned char* data, int width, int height){
    if(!st->active || st->style== STYLE_NONE) return;

    switch(st->style){
        case STYLE_IMPRESSIONISM:
            printf("[ArtStyle] Impressionism effect (stub).\n");
            // Possibly break colors into dabs
            break;
        case STYLE_WATERCOLOR:
            printf("[ArtStyle] Watercolor effect (stub).\n");
            // Possibly do a mild blur, random bleed
            break;
        case STYLE_PIXEL_ART:
            printf("[ArtStyle] Pixel art effect (stub).\n");
            // Could reduce color or do nearest palette
            break;
        default:
            break;
    }
}
