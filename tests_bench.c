/*
 * FILE: tests_bench.c
 * Purpose: Additional bench or stress tests for memory copy,
 * large dictionary voice, or advanced modules.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ultra64.h>
#include "transferpak_base.h"

#define BENCH_BUFFER_SIZE (1024*16)
static unsigned char src_buf[BENCH_BUFFER_SIZE];
static unsigned char dst_buf[BENCH_BUFFER_SIZE];

/*
 * Example bench: test fast_memcpy on 16 KB.
 */
void bench_fast_memcpy() {
    for(int i=0;i<BENCH_BUFFER_SIZE;i++){
        src_buf[i]= (unsigned char)(i & 0xFF);
    }

    // Copy half, then the other half
    int mid= BENCH_BUFFER_SIZE/2;
    fast_memcpy(dst_buf, src_buf, mid);
    fast_memcpy(&dst_buf[mid], &src_buf[mid], BENCH_BUFFER_SIZE-mid);

    // Validate
    for(int i=0;i<BENCH_BUFFER_SIZE;i++){
        if(src_buf[i]!= dst_buf[i]){
            printf("[Bench] mismatch at i=%d\n", i);
            return;
        }
    }
    printf("[Bench] fast_memcpy OK for 16 KB.\n");
}
