#ifndef PROJECT_FILE_H
#define PROJECT_FILE_H

#include <stdbool.h>
#include <stdint.h>
#include "canvas.h"

/*
 * Structures and functions for saving/loading entire project state:
 * project name, author, date, layers, etc.
 */

typedef struct {
    char   name[32];
    char   author[32];
    char   creation_date[16];
    CanvasInfo canvas_info;
} ProjectMeta;

/* 
 * project_save: store metadata + data to Controller Pak or cart 
 * project_load_meta: read project info (like name, date, etc.) 
 * project_requires_expansion: check if the canvas needs expansion 
 */
bool project_save(const ProjectMeta* meta, const void* data, int size);
bool project_load_meta(ProjectMeta* meta_out, int index);
bool project_requires_expansion(const ProjectMeta* meta);

#endif
