#include "ui_advanced.h"
#include <stdio.h>

static UI_Theme s_current_theme= UI_THEME_DEFAULT;
static UI_ToolExtra s_current_tool= TOOL_BRUSH;

/*
 * Extended UI with theming and a "toolbox" concept. 
 */

void ui_advanced_init(UI_Theme theme) {
    s_current_theme= theme;
    printf("[UI Adv] init with theme=%d\n", (int)theme);
}

void ui_advanced_set_theme(UI_Theme theme) {
    s_current_theme= theme;
    printf("[UI Adv] changed theme to=%d\n", (int)theme);
}

void ui_advanced_select_tool(UI_ToolExtra tool) {
    s_current_tool= tool;
    printf("[UI Adv] selected advanced tool=%d\n",(int)tool);
}

void ui_advanced_draw_toolbox() {
    printf("[UI Adv] drawing toolbox theme=%d, tool=%d\n",
           (int)s_current_theme, (int)s_current_tool);
}
