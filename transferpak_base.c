#include "transferpak_base.h"
#include <ultra64.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * This file implements logic to initialize and communicate
 * with the Transfer Pak in a given controller slot.
 */

#define TPAK_MAX_RETRIES 3

static bool       s_tpak_ready      = false;
static int        s_controller_slot = 0;
static OSPfs      s_tpakPfs;
static TpkCartInfo s_cart_info = {
    false,false,true,false, 0x40000,0x8000,0
};

static int  s_reconnection_attempts = 0;
static unsigned char s_global_chunk[256];

/* The external assembly function for memory copying. */
extern void fast_memcpy(void* dst, const void* src, size_t n);

/* XMODEM-like CRC16 used in checksums. */
static unsigned short crc16_xmodem(const unsigned char* data, size_t length) {
    unsigned short crc=0;
    for(size_t i=0;i<length;i++){
        crc ^= (data[i]<<8);
        for(int j=0;j<8;j++){
            if(crc & 0x8000) crc= (crc<<1)^0x1021;
            else             crc<<=1;
        }
    }
    return crc;
}

TpakError tpak_init(int controller_slot) {
    s_tpak_ready=false;
    s_controller_slot= controller_slot;
    s_reconnection_attempts=0;

    // Some default cart info
    s_cart_info.camera_detected     = false;
    s_cart_info.printer_compatible = false;
    s_cart_info.has_sram= true;
    s_cart_info.has_eeprom= false;
    s_cart_info.rom_size= 0x40000;
    s_cart_info.ram_size= 0x8000;
    s_cart_info.eeprom_size= 0;

    memset(&s_tpakPfs,0,sizeof(s_tpakPfs));

    // Initialize the Transfer Pak
    s32 result= osGbpakInit(&s_tpakPfs, controller_slot);
    if(result!=0){
        printf("[TransferPak] init error: %d (slot=%d)\n",(int)result,controller_slot);
        return TPAK_ERR_INIT_FAIL;
    }
    s_tpak_ready=true;
    printf("[TransferPak] init success (slot=%d)\n",controller_slot);
    return TPAK_ERR_NONE;
}

void tpak_close(){
    s_tpak_ready=false;
    printf("[TransferPak] closed.\n");
}

/*
 * tpak_update checks if the Transfer Pak is still connected.
 * If disconnected, tries reinit up to TPAK_MAX_RETRIES times.
 */
bool tpak_update(TpakError* err){
    if(err) *err= TPAK_ERR_NONE;
    if(!s_tpak_ready){
        if(s_reconnection_attempts<TPAK_MAX_RETRIES){
            s_reconnection_attempts++;
            printf("[TransferPak] Not ready. Attempt reconnection (%d/%d)...\n",
                   s_reconnection_attempts, TPAK_MAX_RETRIES);
            TpakError e= tpak_init(s_controller_slot);
            if(e==TPAK_ERR_NONE){
                s_reconnection_attempts=0;
                printf("[TransferPak] Reconnection success.\n");
                return true;
            } else {
                if(err) *err=e;
                return false;
            }
        }
        if(s_reconnection_attempts>=TPAK_MAX_RETRIES){
            printf("[TransferPak] Reconnection failed.\n");
            if(err) *err= TPAK_ERR_MAX_RETRIES;
            return false;
        }
        return false;
    }

    // Check connectivity
    OSPfsState state;
    s32 result= osGbpakCheckConnect(&s_tpakPfs,&state);
    if(result!=0){
        printf("[TransferPak] Cart disconnected (err=%d). Reconnect...\n",(int)result);
        s_tpak_ready=false;
        // attempt reinit
        if(s_reconnection_attempts< TPAK_MAX_RETRIES){
            s_reconnection_attempts++;
            TpakError e= tpak_init(s_controller_slot);
            if(e==TPAK_ERR_NONE){
                s_reconnection_attempts=0;
                printf("[TransferPak] Reconnection success.\n");
                return true;
            } else {
                if(err) *err=e;
                return false;
            }
        }
        if(s_reconnection_attempts>=TPAK_MAX_RETRIES){
            printf("[TransferPak] Full reconnection fail.\n");
            if(err) *err= TPAK_ERR_MAX_RETRIES;
            return false;
        }
        return false;
    }
    return true;
}

TpakError tpak_read_rom(size_t offset, size_t size, void* out_buffer){
    if(!s_tpak_ready){
        return TPAK_ERR_DISCONNECTED;
    }
    if(offset+size> s_cart_info.rom_size){
        return TPAK_ERR_OUT_OF_RANGE;
    }

    size_t remaining= size;
    unsigned char* out_ptr= (unsigned char*)out_buffer;
    size_t current_offset= offset;

    while(remaining>0){
        size_t chunk_size=(remaining>256)?256:remaining;
        if(chunk_size> sizeof(s_global_chunk)){
            return TPAK_ERR_CHUNK_FAIL;
        }
        s32 result= osGbpakReadROM(&s_tpakPfs, current_offset, chunk_size, s_global_chunk);
        if(result!=0){
            return TPAK_ERR_CHUNK_FAIL;
        }
        fast_memcpy(out_ptr, s_global_chunk, chunk_size);

        remaining   -= chunk_size;
        out_ptr     += chunk_size;
        current_offset += chunk_size;
    }
    return TPAK_ERR_NONE;
}

TpakError tpak_read_ram(size_t offset, size_t size, void* out_buffer){
    if(!s_tpak_ready){
        return TPAK_ERR_DISCONNECTED;
    }
    if(offset+size> s_cart_info.ram_size){
        return TPAK_ERR_OUT_OF_RANGE;
    }

    size_t remaining= size;
    unsigned char* out_ptr= (unsigned char*)out_buffer;
    size_t current_offset= offset;

    while(remaining>0){
        size_t chunk_size=(remaining>256)?256:remaining;
        if(chunk_size> sizeof(s_global_chunk)){
            return TPAK_ERR_CHUNK_FAIL;
        }
        s32 result= osGbpakReadRAM(&s_tpakPfs, current_offset, chunk_size, s_global_chunk);
        if(result!=0){
            return TPAK_ERR_CHUNK_FAIL;
        }
        fast_memcpy(out_ptr, s_global_chunk, chunk_size);

        remaining   -= chunk_size;
        out_ptr     += chunk_size;
        current_offset += chunk_size;
    }
    return TPAK_ERR_NONE;
}

TpakError tpak_write_ram(size_t offset, size_t size, const void* in_buffer){
    if(!s_tpak_ready){
        return TPAK_ERR_DISCONNECTED;
    }
    if(!s_cart_info.has_sram){
        return TPAK_ERR_NO_SRAM;
    }
    if(offset+size> s_cart_info.ram_size){
        return TPAK_ERR_OUT_OF_RANGE;
    }

    const unsigned char* in_ptr= (const unsigned char*)in_buffer;
    size_t remaining= size;
    size_t current_offset= offset;

    while(remaining>0){
        size_t chunk_size=(remaining>256)?256:remaining;
        if(chunk_size> sizeof(s_global_chunk)){
            return TPAK_ERR_CHUNK_FAIL;
        }
        fast_memcpy(s_global_chunk, in_ptr, chunk_size);

        s32 result= osGbpakWriteRAM(&s_tpakPfs, current_offset, chunk_size, s_global_chunk);
        if(result!=0){
            return TPAK_ERR_CHUNK_FAIL;
        }
        remaining   -= chunk_size;
        in_ptr      += chunk_size;
        current_offset += chunk_size;
    }
    return TPAK_ERR_NONE;
}

unsigned short tpak_calc_checksum(const void* data, size_t size){
    return crc16_xmodem((const unsigned char*)data,size);
}

TpkCartInfo tpak_get_base_info(){
    return s_cart_info;
}
