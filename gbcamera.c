#include "gbcamera.h"
#include "transferpak_base.h"
#include <stdio.h>
#include <string.h>

static unsigned char camera_default_data[GBCAMERA_MAX_RAM];
static unsigned short known_checksums[8];
static int known_count=0;

/*
 * Creates a default data block for the camera, 
 * calculates a known checksum as reference.
 */
void gb_camera_generate_known_checksums() {
    memset(camera_default_data,0xAA, GBCAMERA_MAX_RAM);
    unsigned short csum= tpak_calc_checksum(camera_default_data, GBCAMERA_MAX_RAM);
    known_checksums[0]= csum;
    known_count=1;
    printf("[GB Camera] Generated known checksum=0x%04X\n", csum);
}

/* 
 * Download photo data from camera RAM, check against known checksums. 
 */
bool gb_camera_download_photos() {
    TpkCartInfo info= tpak_get_base_info();
    if(!info.camera_detected){
        printf("[GB Camera] Not a camera cart.\n");
        return false;
    }
    size_t ram_size=(info.ram_size < GBCAMERA_MAX_RAM)? info.ram_size : GBCAMERA_MAX_RAM;
    if(ram_size==0) return false;

    static unsigned char buffer[GBCAMERA_MAX_RAM];
    memset(buffer,0,GBCAMERA_MAX_RAM);

    TpakError e= tpak_read_ram(0, ram_size, buffer);
    if(e!= TPAK_ERR_NONE){
        printf("[GB Camera] Error reading RAM (err=%d).\n",(int)e);
        return false;
    }
    unsigned short csum= tpak_calc_checksum(buffer, ram_size);
    printf("[GB Camera] Checksum=0x%04X\n", csum);

    bool recognized= false;
    for(int i=0;i<known_count;i++){
        if(csum== known_checksums[i]){
            recognized=true;
            break;
        }
    }
    if(!recognized){
        printf("[GB Camera] WARNING: checksum mismatch.\n");
    }
    return true;
}

/*
 * Upload photos into camera's RAM from a local buffer.
 */
bool gb_camera_upload_photos(const void* data, size_t size) {
    TpkCartInfo info= tpak_get_base_info();
    if(!info.camera_detected){
        printf("[GB Camera] Not a camera cart.\n");
        return false;
    }
    size_t ram_size=(info.ram_size < GBCAMERA_MAX_RAM)? info.ram_size : GBCAMERA_MAX_RAM;
    if(size> ram_size) size= ram_size;

    static unsigned char current[GBCAMERA_MAX_RAM];
    TpakError e= tpak_read_ram(0, ram_size, current);
    if(e!=TPAK_ERR_NONE){
        printf("[GB Camera] Error reading current data (err=%d).\n",(int)e);
        return false;
    }
    unsigned short csum= tpak_calc_checksum(current, ram_size);
    printf("[GB Camera] Current checksum=0x%04X\n", csum);

    e= tpak_write_ram(0, size, data);
    if(e!=TPAK_ERR_NONE){
        printf("[GB Camera] Error writing (err=%d).\n",(int)e);
        return false;
    }
    printf("[GB Camera] Photos uploaded.\n");
    return true;
}
