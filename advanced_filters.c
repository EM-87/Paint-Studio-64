/*
 * FILE: advanced_filters.c
 * Purpose: Implements a library of filters for the painting application.
 *  - Sepia
 *  - Gaussian blur (simplified or a placeholder)
 *  - Edge detect (placeholder)
 *  - Sharpen
 *  - Grayscale
 *  - Bucket fill as a tool-like function
 */

#include "advanced_filters.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/* A simple method to do a box blur or partial blur. */
static void box_blur(unsigned char* data, int width, int height, int radius){
    if(radius<1) return;
    unsigned char* temp= (unsigned char*)malloc(width*height);
    if(!temp) return;

    // Horizontal pass
    for(int y=0;y<height;y++){
        for(int x=0;x<width;x++){
            int sum=0; int count=0;
            for(int k=-radius; k<= radius;k++){
                int nx= x+k;
                if(nx<0) nx=0; 
                if(nx>=width) nx= width-1;
                sum+= data[y*width+ nx];
                count++;
            }
            temp[y*width+ x]= sum/count;
        }
    }

    // Vertical pass
    for(int x=0;x<width;x++){
        for(int y=0;y<height;y++){
            int sum=0; int count=0;
            for(int k=-radius; k<= radius;k++){
                int ny= y+k;
                if(ny<0) ny=0;
                if(ny>=height) ny= height-1;
                sum+= temp[ny*width+ x];
                count++;
            }
            data[y*width+ x]= sum/count;
        }
    }
    free(temp);
}

static void apply_sepia(unsigned char* data, int width, int height, float strength){
    /* If data is grayscale, we do a naive transform:
       gray -> (gray * 0.95) if strength=1, etc. */
    int size= width*height;
    for(int i=0;i<size;i++){
        unsigned char g= data[i];
        float newval= (float)g* 0.95f * strength + (float)g*(1.0f-strength);
        if(newval>255) newval=255;
        if(newval<0) newval=0;
        data[i]= (unsigned char)(newval+0.5f);
    }
    printf("[Filters] SEPIA done (strength=%.2f)\n", strength);
}

/* A placeholder for edge detection. Could do a Sobel or Laplacian. */
static void apply_edge_detect(unsigned char* data, int width, int height){
    printf("[Filters] EDGE DETECT placeholder.\n");
}

/* Minimal sharpen approach (unsharp mask or box difference). */
static void apply_sharpen(unsigned char* data, int width, int height, float strength){
    // We'll do the same approach from v2.1: simple box blur, then unsharp.
    unsigned char* blur= (unsigned char*)malloc(width*height);
    if(!blur) return;

    memcpy(blur, data, width*height);
    // do a quick box blur with radius=1
    box_blur(blur, width, height, 1);

    for(int i=0; i< width*height; i++){
        float orig= data[i];
        float bl=   blur[i];
        float diff= orig- bl;
        float val= orig+ strength* diff;
        if(val<0.0f) val=0.0f;
        if(val>255.0f) val=255.0f;
        data[i]= (unsigned char)(val+0.5f);
    }
    free(blur);
    printf("[Filters] SHARPEN (strength=%.2f)\n", strength);
}

static void apply_grayscale(unsigned char* data, int width, int height){
    /* If data is already grayscale, we do nothing. 
       If it were color, we'd do real conversion. 
       We'll just print a note. */
    printf("[Filters] GRAYSCALE no-op for grayscale data.\n");
}

/* 
 * Called by the user to apply an active filter. 
 */
void filters_apply(const FilterSettings* fs, unsigned char* data, int width, int height){
    if(!fs->active || fs->type==FILTER_NONE) return;
    switch(fs->type){
        case FILTER_SEPIA:
            apply_sepia(data, width, height, fs->strength);
            break;
        case FILTER_GAUSSIAN_BLUR:
            // We do a simple box blur 
            box_blur(data, width, height, (int)(fs->strength+0.5f));
            printf("[Filters] GAUSSIAN BLUR approximation with radius=%d\n", (int)(fs->strength+0.5f));
            break;
        case FILTER_EDGE_DETECT:
            apply_edge_detect(data, width, height);
            break;
        case FILTER_SHARPEN:
            apply_sharpen(data, width, height, fs->strength);
            break;
        case FILTER_GRAYSCALE:
            apply_grayscale(data, width, height);
            break;
        default:
            break;
    }
}

/* Simple 4-direction flood fill for "bucket fill" functionality. */
typedef struct {
    int x,y;
} FillPoint;

static void flood_fill_4(unsigned char* data, int width, int height, int x, int y,
                         unsigned char old_col, unsigned char new_col){
    if(old_col== new_col) return;
    FillPoint stack[4096];
    int top=0;
    stack[top++]= (FillPoint){x,y};

    while(top>0){
        FillPoint p= stack[--top];
        int idx= p.y*width+ p.x;
        if(data[idx]== old_col){
            data[idx]= new_col;
            if(p.x>0)        stack[top++]= (FillPoint){p.x-1, p.y};
            if(p.x<width-1)  stack[top++]= (FillPoint){p.x+1, p.y};
            if(p.y>0)        stack[top++]= (FillPoint){p.x, p.y-1};
            if(p.y<height-1) stack[top++]= (FillPoint){p.x, p.y+1};
            if(top>=4096){
                printf("[BucketFill] stack overflow.\n");
                return;
            }
        }
    }
}

bool bucket_fill(unsigned char* data, int width, int height,
                 int x, int y, unsigned char new_color){
    if(x<0||x>=width||y<0||y>=height) return false;
    unsigned char old_col= data[y*width+ x];
    if(old_col== new_color) return true;
    flood_fill_4(data, width, height, x,y, old_col, new_color);
    printf("[BucketFill] from (%d,%d), old=%d, new=%d\n", x,y, old_col,new_color);
    return true;
}
