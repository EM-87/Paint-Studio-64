#include "file_browser.h"
#include "project_file.h"
#include "expansionpak.h"
#include "ui_interface.h"
#include <stdio.h>
#include <string.h>

#define PROJECT_COUNT 3

/*
 * This module stubs a basic list of "project slots" 
 * and marks them locked if they require expansion and we don't have it.
 */

void file_browser_list_projects() {
    printf("[FileBrowser] Listing projects...\n");
    bool has_expansion= expansionpak_detected();

    for(int i=0; i<PROJECT_COUNT; i++){
        ProjectMeta pm;
        if(project_load_meta(&pm, i)) {
            bool locked= (!has_expansion && project_requires_expansion(&pm));
            if(locked){
                printf("  - %s [LOCKED: expansion needed]\n", pm.name);
                ui_draw_text(10,20+i*10, "[Locked Project]");
            } else {
                printf("  - %s (Author: %s, Date: %s)\n", 
                       pm.name, pm.author, pm.creation_date);
                ui_draw_text(10,20+i*10, pm.name);
            }
        } else {
            printf("  - (slot %d empty?)\n", i);
        }
    }
}

void file_browser_search(const char* query) {
    printf("[FileBrowser] Searching '%s'...\n", query);
    bool has_expansion= expansionpak_detected();

    for(int i=0; i<PROJECT_COUNT; i++){
        ProjectMeta pm;
        if(project_load_meta(&pm, i)) {
            if(strstr(pm.name, query) || strstr(pm.author, query)){
                bool locked= (!has_expansion && project_requires_expansion(&pm));
                if(locked){
                    printf(" [LOCK] %s (Author:%s)\n", pm.name, pm.author);
                } else {
                    printf(" %s (Author:%s, Date:%s)\n", 
                           pm.name, pm.author, pm.creation_date);
                }
            }
        }
    }
}
