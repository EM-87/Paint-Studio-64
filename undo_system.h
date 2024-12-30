#ifndef UNDO_SYSTEM_H
#define UNDO_SYSTEM_H

#include <ultra64.h>
#include <stdbool.h>
#include <time.h>

/*
 * The Undo/Redo system stores up to UNDO_MAX snapshots of layer data.
 * Each snapshot includes a short description (e.g. "Bucket Fill"),
 * plus a timestamp to track when it was created.
 */

#define UNDO_MAX 10
#define UNDO_DESC_LEN 32

/* 
 * UndoRecord holds a snapshot of data 
 * plus metadata like a description and a timestamp.
 */
typedef struct {
    unsigned char* snapshot;
    int size;
    char description[UNDO_DESC_LEN];
    time_t timestamp;
} UndoRecord;

/*
 * UndoStack holds an array of UndoRecords.
 * 'top' is the current index,
 * 'current_size' could be used to track memory usage if desired.
 */
typedef struct {
    UndoRecord history[UNDO_MAX];
    int top;
    int current_size;
} UndoStack;

/*
 * Initializes an UndoStack by clearing all slots and resetting 'top' to -1.
 */
void undo_init(UndoStack* stack);

/*
 * Push a snapshot and a short description onto the UndoStack.
 * If the stack is full, returns false and does nothing.
 */
bool undo_push(UndoStack* stack, const unsigned char* data, int size, const char* desc);

/*
 * Pop the top snapshot from the UndoStack (undo) 
 * and copy its data to out_data. Also returns the record's description (if out_desc != NULL).
 * Returns false if stack is empty.
 */
bool undo_pop(UndoStack* stack, unsigned char* out_data, char* out_desc);

/*
 * For redo, we store a separate stack internally (s_redo_stack).
 * The user calls redo_push to place the "future" state 
 * and redo_pop to restore it. 
 * This is a simplified approach. 
 */
bool redo_push(UndoStack* stack, const unsigned char* data, int size, const char* desc);
bool redo_pop(UndoStack* stack, unsigned char* out_data, char* out_desc);

#endif
