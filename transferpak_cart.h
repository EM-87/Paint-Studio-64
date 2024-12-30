#ifndef TRANSFERPAK_CART_H
#define TRANSFERPAK_CART_H

#include "transferpak_base.h"

/*
 * Detailed detection for specific cart types (like Game Boy Camera or Pokémon).
 */

typedef struct {
    TpkCartInfo base_info;
    bool has_battery;
    unsigned char cart_type;
    char title[17];
    bool pokemon_detected;
    bool gbprinter_detected;
} TpkCartDetect;

/* 
 * Reads header info from the ROM and identifies camera, Pokémon, etc.
 */
TpkCartDetect tpak_detect_cart_advanced();

#endif
