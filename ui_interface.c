#include "ui_interface.h"
#include <stdio.h>

#ifdef REAL_N64
#include <PR/ultratypes.h>
#include <PR/gbi.h>
#endif

void ui_init() {
#ifdef REAL_N64
    printf("[UI] Initializing RDP (REAL_N64).\n");
#else
    printf("[UI] ui_init (mock environment).\n");
#endif
}

void ui_draw_text(int x, int y, const char* text) {
#ifdef REAL_N64
    // Real drawing with RDP
#else
    printf("[UI] draw_text(%d,%d): %s\n", x, y, text);
#endif
}

void ui_show_transferpak_state(bool connected, int attempts) {
#ifdef REAL_N64
    // Possibly display an icon on real hardware
#else
    if(!connected){
        printf("[UI] TransferPak disconnected (attempts=%d)\n", attempts);
    } else {
        printf("[UI] TransferPak connected.\n");
    }
#endif
}

void ui_update_frame() {
#ifdef REAL_N64
    // Might do an osViSwapBuffer call or so
#endif
}

void ui_close() {
#ifdef REAL_N64
    printf("[UI] Closing RDP real.\n");
#else
    printf("[UI] ui_close (mock).\n");
#endif
}
