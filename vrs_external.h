#ifndef VRS_EXTERNAL_H
#define VRS_EXTERNAL_H

#include <stdbool.h>
#include <stdint.h>

/*
 * Stub for external voice recognition integration 
 * (like PocketSphinx or Kaldi).
 */

bool external_vr_init();
bool external_vr_configure(int sample_rate, const char* dictionary_path);
void on_voice_data(const int16_t* samples, int count);
const char* external_vr_get_command();
void external_vr_shutdown();

#endif
