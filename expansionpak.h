#ifndef EXPANSIONPAK_H
#define EXPANSIONPAK_H

#include <ultra64.h>
#include <stdbool.h>

/*
 * Detect if the N64 console has the 8 MB Expansion Pak
 * vs. the default 4 MB. 
 */

bool expansionpak_detected();
u32 expansionpak_get_memory_size();

#endif
