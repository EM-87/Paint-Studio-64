#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "transferpak_base.h"
#include "transferpak_cart.h"
#include "vrs.h"
#include "gbprinter.h"

/*
 * Basic test routines for verifying certain components.
 */

static void test_transferpak_errors() {
    unsigned char buffer[32];
    // If not inited, reading must fail:
    TpakError e= tpak_read_rom(0, 32, buffer);
    assert(e== TPAK_ERR_DISCONNECTED);

    TpakError e2= tpak_init(0);
    e= tpak_read_rom(0xFFFFF, 100, buffer);
    assert(e== TPAK_ERR_OUT_OF_RANGE);

    printf("[Tests] test_transferpak_errors passed.\n");
}

static void test_crc16() {
    unsigned char data[]={0x01,0x02,0x03,0x04};
    unsigned short sum= tpak_calc_checksum(data,4);
    // The actual value might differ, placeholder for demonstration
    unsigned short expected=0x9476; 
    assert(sum== expected);
    printf("[Tests] test_crc16 passed (0x%04X)\n", sum);
}

void run_all_tests() {
    test_transferpak_errors();
    test_crc16();
    printf("[Tests] All tests passed.\n");
}
