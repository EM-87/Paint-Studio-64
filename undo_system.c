#include "undo_system.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * This file implements the Undo/Redo system 
 * with two stacks: 
 *  - The main UndoStack passed in by the user
 *  - A static internal 'RedoStack' (s_redo_stack).
 */

static UndoStack s_redo_stack;  // for storing "future" states when we do an undo

void undo_init(UndoStack* stack) {
    stack->top= -1;
    stack->current_size=0;
    for(int i=0;i<UNDO_MAX;i++){
        stack->history[i].snapshot= NULL;
        stack->history[i].size=0;
        stack->history[i].description[0]= '\0';
        stack->history[i].timestamp=0;
    }
    s_redo_stack.top= -1;
    s_redo_stack.current_size=0;
}

/*
 * Push a snapshot with a description and timestamp.
 */
bool undo_push(UndoStack* stack, const unsigned char* data, int size, const char* desc){
    if(stack->top>= (UNDO_MAX-1)){
        printf("[Undo] Stack is full, cannot push.\n");
        return false;
    }
    stack->top++;
    UndoRecord* ur= &stack->history[stack->top];
    ur->size= size;
    ur->snapshot= (unsigned char*)malloc(size);
    if(!ur->snapshot){
        printf("[Undo] malloc failed.\n");
        stack->top--;
        return false;
    }
    memcpy(ur->snapshot, data, size);

    // Store up to 31 chars plus a null terminator
    if(desc){
        strncpy(ur->description, desc, UNDO_DESC_LEN-1);
        ur->description[UNDO_DESC_LEN-1]= '\0';
    } else {
        ur->description[0]= '\0';
    }

    ur->timestamp= time(NULL);
    // stack->current_size could track memory usage if we want
    return true;
}

/*
 * Pop the top snapshot from the stack (undo).
 * If out_desc is non-NULL, we copy the record's description into it.
 * Freed memory is reclaimed so we don't leak.
 */
bool undo_pop(UndoStack* stack, unsigned char* out_data, char* out_desc){
    if(stack->top<0){
        printf("[Undo] No more records to pop.\n");
        return false;
    }
    UndoRecord* ur= &stack->history[stack->top];
    if(!ur->snapshot){
        printf("[Undo] top record has no snapshot?\n");
        return false;
    }
    memcpy(out_data, ur->snapshot, ur->size);

    if(out_desc){
        strcpy(out_desc, ur->description);
    }

    free(ur->snapshot);
    ur->snapshot= NULL;
    ur->size=0;
    ur->description[0]= '\0';
    stack->top--;
    return true;
}

/*
 * The redo stack is a separate UndoStack so we can store future states.
 * The user calls redo_push(...) after popping from main stack, 
 * or we could do it automatically in an 'undo' function.
 */
bool redo_push(UndoStack* stack, const unsigned char* data, int size, const char* desc){
    // We'll push into s_redo_stack
    if(s_redo_stack.top>= (UNDO_MAX-1)){
        printf("[Redo] Stack is full, cannot push.\n");
        return false;
    }
    s_redo_stack.top++;
    UndoRecord* ur= &s_redo_stack.history[s_redo_stack.top];
    ur->size= size;
    ur->snapshot= (unsigned char*)malloc(size);
    if(!ur->snapshot){
        s_redo_stack.top--;
        printf("[Redo] malloc fail.\n");
        return false;
    }
    memcpy(ur->snapshot, data, size);

    if(desc){
        strncpy(ur->description, desc, UNDO_DESC_LEN-1);
        ur->description[UNDO_DESC_LEN-1]= '\0';
    } else {
        ur->description[0]= '\0';
    }

    ur->timestamp= time(NULL);
    return true;
}

/*
 * redo_pop retrieves from s_redo_stack and copies to out_data.
 * If out_desc is provided, we copy the record's description as well.
 */
bool redo_pop(UndoStack* stack, unsigned char* out_data, char* out_desc){
    if(s_redo_stack.top<0){
        printf("[Redo] Nothing to redo.\n");
        return false;
    }
    UndoRecord* ur= &s_redo_stack.history[s_redo_stack.top];
    memcpy(out_data, ur->snapshot, ur->size);

    if(out_desc){
        strcpy(out_desc, ur->description);
    }

    free(ur->snapshot);
    ur->snapshot= NULL;
    ur->size= 0;
    ur->description[0]= '\0';
    s_redo_stack.top--;
    return true;
}
