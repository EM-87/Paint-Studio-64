#ifndef CONFIG_H
#define CONFIG_H

#include <stdbool.h>
#include "vrs.h"

/*
 * A basic struct storing the app config, 
 * possibly loaded from "settings.cfg".
 */

typedef struct {
    bool use_trie_for_voice;
    bool show_detailed_logs;
    VRS_Language default_language;
    int max_reconnect_time;
    int levenshtein_sensitivity;
} AppConfig;

/* Attempts to load the config from a file. */
bool config_load(AppConfig* cfg, const char* filename);

#endif
