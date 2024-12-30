#ifndef COLOR_PALETTE_H
#define COLOR_PALETTE_H

#include <ultra64.h>
#include <stdbool.h>

/*
 * Manages a custom color palette with up to 256 entries (RGB).
 */

#define MAX_COLORS 256

typedef struct {
    unsigned char r,g,b;
} ColorRGB;

typedef struct {
    char name[32];
    ColorRGB colors[MAX_COLORS];
    int color_count;
} ColorPalette;

/* Create an empty palette with a name. */
void palette_create(ColorPalette* cp, const char* name);

/* Add a color. */
bool palette_add_color(ColorPalette* cp, unsigned char r, unsigned char g, unsigned char b);

/* Save / Load the palette from memory. */
bool palette_save(const ColorPalette* cp);
bool palette_load(ColorPalette* cp);

/* Export to a project slot or something. */
bool palette_export_to_project(const ColorPalette* cp, int project_index);

#endif
