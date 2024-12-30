#include "project_file.h"
#include <stdio.h>
#include <string.h>

/*
 * Implementation stubs for saving/loading project data 
 * to a memory card slot. 
 */

bool project_save(const ProjectMeta* meta, const void* data, int size) {
    printf("[Project] Saving '%s' (Author=%s, Date=%s)\n",
           meta->name, meta->author, meta->creation_date);
    // Actual memory card code omitted for brevity.
    // Typically uses osPfs calls or similar.
    return true;
}

bool project_load_meta(ProjectMeta* meta_out, int index) {
    // Stub: simulate reading from slot "index"
    sprintf(meta_out->name, "ProjectSlot%d", index);
    strcpy(meta_out->author, "Anon");
    strcpy(meta_out->creation_date, "01/01/2000");
    meta_out->canvas_info.width= 320;
    meta_out->canvas_info.height= 240;
    meta_out->canvas_info.layers= 3;
    meta_out->canvas_info.requires_expansion= false;
    return true;
}

bool project_requires_expansion(const ProjectMeta* meta) {
    return meta->canvas_info.requires_expansion;
}
