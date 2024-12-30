#ifndef UI_INTERFACE_H
#define UI_INTERFACE_H

#include <stdbool.h>

/*
 * Basic interface for drawing text or shapes on screen,
 * either in a mock environment or using RDP in REAL_N64 mode.
 */

void ui_init();
void ui_draw_text(int x, int y, const char* text);
void ui_show_transferpak_state(bool connected, int attempts);
void ui_update_frame();
void ui_close();

#endif
