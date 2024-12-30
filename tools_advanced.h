#ifndef TOOLS_ADVANCED_H
#define TOOLS_ADVANCED_H

#include "layer_system.h"

/*
 * Advanced drawing tools: blur, glitter, text, plus a pressure-based brush.
 */

void tool_blur(CanvasLayer* layer, int x, int y, int radius);
void tool_glitter(CanvasLayer* layer, int x, int y, int size);
void tool_text(CanvasLayer* layer, const char* text, int x, int y);

/**
 * Example: a brush that uses "pressure" (0..1) to determine color or coverage
 */
void tool_pressure_brush(CanvasLayer* layer, int x, int y, int radius, float pressure);

#endif
