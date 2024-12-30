#ifndef TOOLS_INSPIRED_H
#define TOOLS_INSPIRED_H

#include "layer_system.h"

/*
 * Tools inspired by "Splatoon" (ink shots) or "Mario Paint" (stamps).
 */

void tool_splatoon(LayerInfo* info, int x, int y, int size);
void tool_mario_paint_stamp(LayerInfo* info, int x, int y, int stamp_id);

#endif
