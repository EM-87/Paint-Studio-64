#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include <ultra64.h>
#include <stdbool.h>

#define MAX_PLAYERS 4

/*
 * Multiplayer system for up to 4 players, each with a controller,
 * a cursor, and a selected tool.
 */

typedef struct {
    int controller_id;
    int cursor_x, cursor_y;
    int selected_tool; 
    bool active;
} PlayerInfo;

/* Initialize players for co-op drawing. */
void multiplayer_init(PlayerInfo* players, int player_count);

/* Read input from multiple controllers (stubbed). */
void handle_multiplayer_input(PlayerInfo* players, int player_count);

/* Render cursors/UI for each player. */
void render_multiplayer_ui(const PlayerInfo* players, int player_count);

/* Dynamically assign a tool to a player. */
void assign_tool_to_player(PlayerInfo* players, int player_id, int tool_id);

#endif
