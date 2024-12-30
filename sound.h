#ifndef SOUND_H
#define SOUND_H

#include <ultra64.h>
#include <stdbool.h>

/*
 * Basic sound system:
 * background music (multiple tracks),
 * SFX for brushes, etc.
 */

typedef enum {
    SFX_TOOL_SELECT=0,
    SFX_DRAW_LINE,
    SFX_FILL_AREA,
    SFX_LAYER_SWITCH,
    SFX_MAX
} SoundEffect;

/* Initialize the sound system. */
bool sound_init();

/* Play an effect. */
void sound_play_effect(SoundEffect sfx);

/* Close the sound system. */
void sound_close();

#endif
