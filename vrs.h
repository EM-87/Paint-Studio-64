#ifndef VRS_H
#define VRS_H

#include <stdbool.h>

/*
 * Basic Voice Recognition System (VRS).
 * Allows approximate matching of short commands.
 */

typedef enum {
    VRS_LANG_ENGLISH=0,
    VRS_LANG_SPANISH,
    VRS_LANG_JAPANESE
} VRS_Language;

typedef struct {
    VRS_Language current_lang;
    bool enabled;
    bool approximate_matching;
    bool use_trie;
    int levenshtein_sensitivity;
} VRS_Context;

/* Some alias struct for synonyms. */
typedef struct {
    const char* alias;
    const char* target;
} AliasMap;

/* Initialization and language changes. */
bool vrs_init(VRS_Context* ctx, VRS_Language lang, bool approximate);
bool vrs_change_language(VRS_Context* ctx, VRS_Language lang);
void vrs_shutdown(VRS_Context* ctx);

/* Mock input for voice. */
void vrs_mock_voice_input(const char* input);
const char* vrs_get_last_input();

/* The main update call that processes the input string. */
const char* vrs_update(VRS_Context* ctx);

/* 
 * Levenshtein distance for approximate matching. 
 */
int vrs_levenshtein(const char* s1, const char* s2);
int vrs_levenshtein_optimized(const char* s1, const char* s2, int max_distance);

/* 
 * If we have a dictionary-based approach, we can store synonyms 
 * and do alias resolution.
 */
const char* vrs_resolve_alias(AliasMap* map, const char* alias);

#endif
