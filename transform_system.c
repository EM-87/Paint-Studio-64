#include "transform_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Flip horizontally or vertically. */
bool transform_flip(unsigned char* data, int width, int height, bool horizontal){
    int half= horizontal? width/2 : height/2;
    if(horizontal){
        for(int y=0;y<height;y++){
            for(int x=0;x< half;x++){
                int left= y*width + x;
                int right= y*width + (width-1 - x);
                unsigned char tmp= data[left];
                data[left]= data[right];
                data[right]= tmp;
            }
        }
        printf("[Transform] flip horizontally done.\n");
    } else {
        for(int x=0;x<width;x++){
            for(int y=0;y< half;y++){
                int top= y*width+ x;
                int bottom= (height-1-y)*width+ x;
                unsigned char tmp= data[top];
                data[top]= data[bottom];
                data[bottom]= tmp;
            }
        }
        printf("[Transform] flip vertically done.\n");
    }
    return true;
}

/* A naive skew stub. */
bool transform_skew(unsigned char* data, int width, int height, float skewX, float skewY){
    printf("[Transform] skew(%.2f,%.2f) (stub)\n", skewX, skewY);
    return true;
}

/* A stub for scaling in place. Real approach might require new buffer. */
bool transform_scale(unsigned char* data, int width, int height, float factor){
    printf("[Transform] scale factor=%.2f (stub)\n", factor);
    return true;
}
