#include "tools_advanced.h"
#include <stdio.h>
#include <math.h>

/*
 * Implementation stubs for advanced drawing tools.
 * Real code might do per-pixel calculations in the layer data.
 */

void tool_blur(CanvasLayer* layer, int x, int y, int radius){
    if(!layer->data) return;
    printf("[ToolAdv] blur at (%d,%d) radius=%d\n", x,y,radius);
    // Implementation omitted for brevity
}

void tool_glitter(CanvasLayer* layer, int x, int y, int size){
    if(!layer->data) return;
    printf("[ToolAdv] glitter at (%d,%d) size=%d\n", x,y,size);
}

void tool_text(CanvasLayer* layer, const char* text, int x, int y){
    if(!layer->data) return;
    printf("[ToolAdv] text='%s' at (%d,%d)\n", text, x,y);
}

void tool_pressure_brush(CanvasLayer* layer, int x, int y, int radius, float pressure){
    if(!layer->data) return;
    if(pressure<0.0f) pressure=0.0f;
    if(pressure>1.0f) pressure=1.0f;

    unsigned char color= (unsigned char)(255.0f*pressure);
    int width= 320; // real code might track actual width
    int height= 240;
    printf("[ToolAdv] pressure brush at (%d,%d), radius=%d, pressure=%.2f\n", x,y,radius,pressure);

    // Fill a circle
    for(int dy=-radius; dy<=radius; dy++){
        for(int dx=-radius; dx<=radius; dx++){
            float dist= sqrtf((float)(dx*dx + dy*dy));
            if(dist<= radius){
                int xx= x+dx;
                int yy= y+dy;
                if(xx>=0&&xx<width&&yy>=0&&yy<height){
                    layer->data[ yy*width + xx ]= color;
                }
            }
        }
    }
}
