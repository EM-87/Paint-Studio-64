#ifndef VOICE_ADVANCED_H
#define VOICE_ADVANCED_H

#include <ultra64.h>
#include <stdbool.h>

/*
 * A more advanced approach to voice input, 
 * possibly parsing entire phrases or sentences.
 */

bool voice_adv_init();
void voice_adv_shutdown();
const char* voice_adv_process_sentence(const char* sentence);

#endif
