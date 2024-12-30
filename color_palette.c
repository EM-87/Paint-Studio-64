#include "color_palette.h"
#include <stdio.h>
#include <string.h>

void palette_create(ColorPalette* cp, const char* name){
    strncpy(cp->name, name, 31);
    cp->name[31]= '\0';
    cp->color_count=0;
    printf("[Palette] created '%s'\n", cp->name);
}

bool palette_add_color(ColorPalette* cp, unsigned char r, unsigned char g, unsigned char b){
    if(cp->color_count>= MAX_COLORS) return false;
    cp->colors[ cp->color_count ]= (ColorRGB){ r,g,b };
    cp->color_count++;
    printf("[Palette] color #%d = (%d,%d,%d)\n", cp->color_count, r,g,b);
    return true;
}

bool palette_save(const ColorPalette* cp){
    printf("[Palette] Saving '%s' with %d colors.\n", cp->name, cp->color_count);
    // Stub for memory card or file
    return true;
}

bool palette_load(ColorPalette* cp){
    printf("[Palette] Loading a palette...\n");
    strcpy(cp->name, "DefaultLoaded");
    cp->color_count=3;
    cp->colors[0]=(ColorRGB){255,0,0};
    cp->colors[1]=(ColorRGB){0,255,0};
    cp->colors[2]=(ColorRGB){0,0,255};
    return true;
}

bool palette_export_to_project(const ColorPalette* cp, int project_index){
    printf("[Palette] Export '%s' to project %d.\n", cp->name, project_index);
    return true;
}
