#ifndef PREVIEW_RENDERER_H
#define PREVIEW_RENDERER_H

#include <ultra64.h>
#include "canvas.h"

/*
 * Renders a small preview (thumbnail) of the canvas or layer 
 * in a separate buffer, for displaying in a UI or gallery.
 */

void generate_preview(const CanvasInfo* canvas_info, const unsigned char* data, 
                      int src_width, int src_height,
                      void* output_buffer, int out_width, int out_height);

void draw_preview(const void* buffer, int width, int height, int x, int y);

#endif
