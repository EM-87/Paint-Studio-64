#ifndef FILE_BROWSER_H
#define FILE_BROWSER_H

/*
 * A minimal file browser interface for listing projects 
 * on the memory card, searching by name or tags, etc.
 */

void file_browser_list_projects();
void file_browser_search(const char* query);

#endif
