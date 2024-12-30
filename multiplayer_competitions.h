#ifndef MULTIPLAYER_COMPETITIONS_H
#define MULTIPLAYER_COMPETITIONS_H

#include "multiplayer.h"

/*
 * Adds competitive or challenge modes for multiplayer.
 */

void competition_mode_init();
void competition_update(PlayerInfo* players, int player_count);
bool competition_is_finished();

#endif
