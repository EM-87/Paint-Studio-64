#ifndef TRANSFERPAK_BASE_H
#define TRANSFERPAK_BASE_H

#include <ultra64.h>
#include <stdbool.h>
#include <stddef.h>
#include "transferpak_errors.h"

/*
 * Provides a base interface to handle the Transfer Pak:
 * initialization, reading/writing from cart RAM/ROM, checking connectivity.
 */

typedef struct {
    bool camera_detected;
    bool printer_compatible;
    bool has_sram;
    bool has_eeprom;
    size_t rom_size;
    size_t ram_size;
    size_t eeprom_size;
} TpkCartInfo;

/* Initialize the Transfer Pak in a certain controller slot. */
TpakError tpak_init(int controller_slot);
void tpak_close();

/* Checks and updates Transfer Pak connectivity. */
bool tpak_update(TpakError* err);

/* Functions to read from cart ROM/RAM or write to cart RAM. */
TpakError tpak_read_rom(size_t offset, size_t size, void* out_buffer);
TpakError tpak_read_ram(size_t offset, size_t size, void* out_buffer);
TpakError tpak_write_ram(size_t offset, size_t size, const void* in_buffer);

/* Basic checksum calculation used in some modules. */
unsigned short tpak_calc_checksum(const void* data, size_t size);

/* Get info about the cart (size, SRAM presence, etc.). */
TpkCartInfo tpak_get_base_info();

/* MIPS assembly memory copy, declared externally. */
void fast_memcpy(void* dst, const void* src, size_t n);

#endif
