#include "transferpak_cart.h"
#include <stdio.h>
#include <string.h>

/*
 * Implementation that reads the ROM header at 0x0134 
 * and extracts certain bytes to detect camera, etc.
 */

TpkCartDetect tpak_detect_cart_advanced() {
    TpkCartDetect result;
    result.base_info = tpak_get_base_info();
    result.has_battery = false;
    result.cart_type   = 0;
    memset(result.title, 0, sizeof(result.title));
    result.pokemon_detected   = false;
    result.gbprinter_detected = false;

    unsigned char header[32];
    memset(header, 0, sizeof(header));

    /* 
     * Typically, 0x0134 in the GB cart header is the game title region, 
     * plus 0x0147 is cart type, etc.
     */
    TpakError err= tpak_read_rom(0x0134, 32, header);
    if(err!= TPAK_ERR_NONE) {
        printf("[tpak_cart] Error reading cart header (err=%d).\n",(int)err);
        return result;
    }
    strncpy(result.title, (char*)header,16);
    result.title[16] = '\0';

    unsigned char type_byte = header[0x13]; // cart type
    result.cart_type= type_byte;

    switch (type_byte) {
        case 0x03: case 0x06: case 0x09:
        case 0x0F: case 0x13: case 0x1B: case 0x1E:
            result.has_battery = true;
            break;
        default:
            result.has_battery = false;
            break;
    }

    if (strstr(result.title,"CAMERA")) {
        result.base_info.camera_detected= true;
    }
    if (strstr(result.title,"ZELDA")) {
        result.base_info.printer_compatible= true;
    }
    if (strstr(result.title,"POKEMON") || strstr(result.title,"Pokemon")) {
        result.pokemon_detected= true;
    }
    if (strstr(result.title,"GBPRNT") || strstr(result.title,"PRINTER")) {
        result.gbprinter_detected= true;
    }

    return result;
}
