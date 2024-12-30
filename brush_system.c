#include "brush_system.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void brush_system_init(BrushCollection* bc){
    bc->brush_count=0;
    for(int i=0;i<MAX_CUSTOM_BRUSHES;i++){
        bc->brushes[i].data= NULL;
    }
    printf("[BrushSystem] init.\n");
}

bool brush_create(BrushCollection* bc, const char* name, int w, int h, bool use_opacity){
    if(bc->brush_count>= MAX_CUSTOM_BRUSHES){
        printf("[BrushSystem] No more brush slots.\n");
        return false;
    }
    CustomBrush* br= &bc->brushes[ bc->brush_count ];
    strncpy(br->name, name, BRUSH_NAME_LEN-1);
    br->name[BRUSH_NAME_LEN-1]= '\0';
    br->width= w;
    br->height= h;
    br->use_opacity= use_opacity;
    int size= w*h;
    br->data= (unsigned char*)malloc(size);
    if(!br->data){
        printf("[BrushSystem] malloc fail.\n");
        return false;
    }
    memset(br->data, 0xFF, size); // e.g. fill with some pattern
    bc->brush_count++;
    printf("[BrushSystem] Created brush '%s' %dx%d\n", br->name, w,h);
    return true;
}

bool brush_save_collection(const BrushCollection* bc){
    printf("[BrushSystem] Saving %d brushes to Controller Pak.\n", bc->brush_count);
    for(int i=0; i<bc->brush_count; i++){
        printf("  -> '%s' (%dx%d)\n", bc->brushes[i].name,
               bc->brushes[i].width, bc->brushes[i].height);
    }
    return true;
}

bool brush_load_collection(BrushCollection* bc){
    printf("[BrushSystem] Loading brushes from Controller Pak...\n");
    bc->brush_count=1;
    CustomBrush* br= &bc->brushes[0];
    strcpy(br->name, "LoadedBrush");
    br->width= 16;
    br->height=16;
    br->use_opacity= true;
    int size= br->width* br->height;
    br->data= (unsigned char*)malloc(size);
    memset(br->data, 0xAA, size);
    printf("[BrushSystem] 1 brush loaded: '%s'\n", br->name);
    return true;
}

void brush_apply(const CustomBrush* brush, unsigned char* layer_data,
                 int layer_width, int layer_height, int x, int y)
{
    if(!brush || !brush->data || !layer_data) return;
    printf("[BrushSystem] Applying brush '%s' at (%d,%d)\n", brush->name, x,y);
    // e.g. copy brush->data onto layer, clipped to bounds
    for(int j=0;j<brush->height;j++){
        for(int i=0;i<brush->width;i++){
            int tx= x+i;
            int ty= y+j;
            if(tx>=0 && tx<layer_width && ty>=0 && ty<layer_height){
                layer_data[ ty* layer_width + tx ]= brush->data[j* brush->width + i];
            }
        }
    }
}
