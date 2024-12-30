#include "expansionpak.h"
#include <ultra64.h>
#include <stdio.h>

bool expansionpak_detected() {
    extern u32 osMemSize; // from <ultra64.h> or runtime
    return (osMemSize> 4*1024*1024);
}

u32 expansionpak_get_memory_size() {
    extern u32 osMemSize;
    return osMemSize;
}
