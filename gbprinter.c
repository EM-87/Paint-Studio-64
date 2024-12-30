#include "gbprinter.h"
#include "transferpak_base.h"
#include <stdio.h>
#include <string.h>

/*
 * Basic stubs for interacting with a "printer_compatible" cart. 
 */

bool gb_printer_download_images() {
    TpkCartInfo info= tpak_get_base_info();
    if(!info.printer_compatible){
        printf("[GBPrinter] Cart not printer-compatible.\n");
        return false;
    }
    size_t ram_size= (info.ram_size <0x2000)? info.ram_size : 0x2000;
    static unsigned char buffer[0x2000];

    TpakError e= tpak_read_ram(0, ram_size, buffer);
    if(e!=TPAK_ERR_NONE){
        printf("[GBPrinter] Error reading RAM (err=%d)\n",(int)e);
        return false;
    }
    printf("[GBPrinter] Images downloaded.\n");
    return true;
}

bool gb_printer_print_data(const void* data, size_t size) {
    TpkCartInfo info= tpak_get_base_info();
    if(!info.printer_compatible){
        printf("[GBPrinter] Not a printer-compatible cart.\n");
        return false;
    }
    if(size>0x2000) size=0x2000;

    TpakError e= tpak_write_ram(0, size, data);
    if(e!=TPAK_ERR_NONE){
        printf("[GBPrinter] Error printing: %d\n",(int)e);
        return false;
    }
    printf("[GBPrinter] Printing data...\n");
    return true;
}
