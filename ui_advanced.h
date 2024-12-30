#ifndef UI_ADVANCED_H
#define UI_ADVANCED_H

#include <ultra64.h>
#include <stdbool.h>

/*
 * Extended UI functionality for themes, advanced tool selection, etc.
 */

typedef enum {
    UI_THEME_DEFAULT=0,
    UI_THEME_DARK,
    UI_THEME_LIGHT
} UI_Theme;

typedef enum {
    TOOL_BRUSH=0,
    TOOL_ERASER,
    TOOL_FILL,
    TOOL_SPRAY,
    TOOL_ADVANCED_1,
    TOOL_ADVANCED_2
} UI_ToolExtra;

/* Initialize advanced UI with a theme. */
void ui_advanced_init(UI_Theme theme);

/* Switch theme at runtime. */
void ui_advanced_set_theme(UI_Theme theme);

/* Select a more advanced tool. */
void ui_advanced_select_tool(UI_ToolExtra tool);

/* Draw a toolbox or palette on screen. */
void ui_advanced_draw_toolbox();

#endif
