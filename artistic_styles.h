#ifndef ARTISTIC_STYLES_H
#define ARTISTIC_STYLES_H

#include <ultra64.h>
#include <stdbool.h>

/*
 * Allows applying artistic filters or transformations:
 *  - IMPRESSIONISM
 *  - WATERCOLOR
 *  - PIXEL_ART
 */

typedef enum {
    STYLE_NONE=0,
    STYLE_IMPRESSIONISM,
    STYLE_WATERCOLOR,
    STYLE_PIXEL_ART
} ArtStyle;

typedef struct {
    ArtStyle style;
    bool active;
} ArtStyleSettings;

/*
 * Applies the selected style to an 8-bit buffer.
 */
void style_apply(const ArtStyleSettings* st, unsigned char* data, int width, int height);

#endif
