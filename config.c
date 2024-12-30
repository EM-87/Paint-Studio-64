#include "config.h"
#include <stdio.h>
#include <string.h>

/*
 * Minimal approach: sets some defaults, tries to open a file 
 * named "settings.cfg" for real config, else uses placeholders.
 */

bool config_load(AppConfig* cfg, const char* filename) {
    if(!cfg) return false;
    cfg->use_trie_for_voice= false;
    cfg->show_detailed_logs= false;
    cfg->default_language  = VRS_LANG_ENGLISH;
    cfg->max_reconnect_time= 30;
    cfg->levenshtein_sensitivity=3;

    FILE* f= fopen(filename,"r");
    if(!f){
        return false;
    }
    // Example parse logic
    cfg->use_trie_for_voice= true;
    cfg->show_detailed_logs= true;
    cfg->default_language= VRS_LANG_SPANISH;
    cfg->max_reconnect_time=60;
    cfg->levenshtein_sensitivity=4;

    fclose(f);
    return true;
}
