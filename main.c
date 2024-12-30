#include <ultra64.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/*
 * FILE: main.c
 * The central entry point for "N64 Paint Studio v2.2 (Capped Resolution)."
 * Demonstrates how to tie together expansions, layering, selection, 
 * advanced filters, transformations, zoom, etc.
 */

// Includes from the codebase
#include "transferpak_base.h"
#include "layer_system.h"
#include "undo_system.h"
#include "selection_system.h"
#include "export_system.h"
#include "canvas_extended.h"
#include "anti_alias.h"
#include "transform_system.h"
#include "advanced_filters.h"
#include "expansionpak.h"
#include "zoom_system.h"
#include "multiplayer.h"
#include "brush_system.h"
#include "adjustment_layer.h"
#include "tools_advanced.h"
#include "tests_bench.c" // or run_all_tests from tests
// etc.

#define DEF_WIDTH  320
#define DEF_HEIGHT 240

static LayerInfo s_layer_info;
static UndoStack s_undo_stack;
static RectSelection s_sel;
static FilterSettings s_filter_fs= { FILTER_NONE, 0.0f, false };
static bool s_has_expansion= false;

/* Example function to do an auto-save snapshot to undo, with description. */
static void auto_save_snapshot(const char* desc){
    int cl= s_layer_info.current_layer;
    if(cl>=0){
        undo_push(&s_undo_stack, 
                  s_layer_info.layers[cl].data, DEF_WIDTH*DEF_HEIGHT,
                  desc);
    }
}

/* Minimal "process_cmd" style for demonstration. */
static void process_cmd(const char* cmd){
    if(!strcmp(cmd,"ZOOM_IN")) { zoom_in(); return; }
    if(!strcmp(cmd,"ZOOM_OUT")){ zoom_out(); return; }

    if(!strcmp(cmd,"APPLY_SHARPEN")){
        s_filter_fs.type= FILTER_SHARPEN;
        s_filter_fs.strength= 1.0f;
        s_filter_fs.active= true;
        filters_apply(&s_filter_fs, s_layer_info.layers[s_layer_info.current_layer].data, DEF_WIDTH, DEF_HEIGHT);
        s_filter_fs.active= false;
        return;
    }
    if(!strcmp(cmd,"BUCKET_FILL")){
        bucket_fill(s_layer_info.layers[s_layer_info.current_layer].data,
                    DEF_WIDTH, DEF_HEIGHT, 10,10, 128);
        return;
    }
    // Additional commands omitted for brevity...
}

int main(void){
    printf("[Main] Starting N64 Paint Studio v2.2 (Capped resolution logic)\n");
    s_has_expansion= expansionpak_detected();
    layer_system_init(&s_layer_info, 3, DEF_WIDTH*DEF_HEIGHT);
    undo_init(&s_undo_stack);
    zoom_system_init();

    // Suppose we run a bench or test:
    bench_fast_memcpy();

    // Example usage:
    process_cmd("BUCKET_FILL");
    auto_save_snapshot("after bucket fill");

    process_cmd("APPLY_SHARPEN");
    auto_save_snapshot("after sharpen");

    process_cmd("ZOOM_IN");
    // etc.

    printf("[Main] Done.\n");
    return 0;
}
