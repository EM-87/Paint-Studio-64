#include "preview_renderer.h"
#include <stdio.h>
#include <string.h>

/*
 * Minimal approach to create a downscaled thumbnail 
 * from an 8-bit data buffer, then draw it in UI.
 */

void generate_preview(const CanvasInfo* canvas_info, const unsigned char* data,
                      int src_width, int src_height,
                      void* output_buffer, int out_width, int out_height)
{
    // We'll do a naive nearest-neighbor scale
    unsigned char* dst= (unsigned char*)output_buffer;
    for(int y=0; y< out_height; y++){
        for(int x=0; x< out_width; x++){
            float rx= (float)x/(out_width-1)*(src_width-1);
            float ry= (float)y/(out_height-1)*(src_height-1);
            int sx= (int)(rx+0.5f);
            int sy= (int)(ry+0.5f);
            dst[y*out_width + x]= data[ sy*src_width + sx ];
        }
    }
    printf("[Preview] Generated %dx%d thumbnail from %dx%d\n",
           out_width, out_height, src_width, src_height);
}

void draw_preview(const void* buffer, int width, int height, int x, int y)
{
    printf("[Preview] draw_preview at screen (%d,%d) size %dx%d\n",
           x,y, width,height);
    // On real hardware, we'd push the image to RDP or do loadTexture block.
}
