#include "gallery_advanced.h"
#include <stdio.h>
#include <string.h>

#define MAX_TAGS 8
typedef struct {
    char tags[MAX_TAGS][16];
    int tag_count;
} ProjectTags;

static ProjectTags s_tags_db[16]; // up to 16 projects

void gallery_show(){
    printf("[Gallery] Show advanced gallery...\n");
    // We might list each project’s tags, etc.
}

void gallery_add_tag(int project_index, const char* tag){
    if(project_index<0|| project_index>=16) return;
    ProjectTags* pt= &s_tags_db[project_index];
    if(pt->tag_count< MAX_TAGS){
        strncpy(pt->tags[ pt->tag_count ], tag, 15);
        pt->tags[ pt->tag_count ][15]= '\0';
        pt->tag_count++;
        printf("[Gallery] Tag '%s' added to project %d\n", tag, project_index);
    }
}

void gallery_search_by_tag(const char* tag){
    printf("[Gallery] Searching for tag '%s'\n", tag);
    for(int i=0;i<16;i++){
        for(int j=0;j<s_tags_db[i].tag_count;j++){
            if(!strcmp(s_tags_db[i].tags[j], tag)){
                printf("  Project %d has tag '%s'\n", i, tag);
            }
        }
    }
}
