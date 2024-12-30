#ifndef GALLERY_ADVANCED_H
#define GALLERY_ADVANCED_H

#include "project_file.h"

/*
 * A more advanced gallery system that organizes projects 
 * with tags, searching, etc.
 */

void gallery_show();
void gallery_add_tag(int project_index, const char* tag);
void gallery_search_by_tag(const char* tag);

#endif
