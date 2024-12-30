#include "multiplayer.h"
#include <stdio.h>
#include <string.h>

/*
 * Implementation stubs for a multiplayer co-op system,
 * up to 4 players controlling different cursors or tools.
 */

static int s_player_count= 0;

void multiplayer_init(PlayerInfo* players, int player_count){
    if(player_count> MAX_PLAYERS) player_count= MAX_PLAYERS;
    s_player_count= player_count;
    for(int i=0; i<player_count; i++){
        players[i].controller_id= i;
        players[i].cursor_x= 100 + i*20;
        players[i].cursor_y= 100 + i*10;
        players[i].selected_tool= 0; 
        players[i].active= true;
        printf("[Multiplayer] Player %d initialized.\n", i);
    }
}

void handle_multiplayer_input(PlayerInfo* players, int player_count){
    for(int i=0; i<player_count; i++){
        if(!players[i].active) continue;
        // Simulate cursor movement
        players[i].cursor_x++;
        if(players[i].cursor_x> 240) players[i].cursor_x= 100;
    }
}

void render_multiplayer_ui(const PlayerInfo* players, int player_count){
    for(int i=0; i<player_count; i++){
        if(!players[i].active) continue;
        printf("[MultiplayerUI] P%d at (%d,%d), tool=%d\n",
               i, players[i].cursor_x, players[i].cursor_y, players[i].selected_tool);
    }
}

void assign_tool_to_player(PlayerInfo* players, int player_id, int tool_id){
    if(player_id<0 || player_id>= s_player_count){
        printf("[Multiplayer] Invalid player ID %d\n", player_id);
        return;
    }
    players[player_id].selected_tool= tool_id;
    printf("[Multiplayer] Assigned tool %d to player %d\n", tool_id, player_id);
}
