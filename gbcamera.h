#ifndef GBCAMERA_H
#define GBCAMERA_H

#include <stdbool.h>
#include <stddef.h>

/*
 * Routines to handle Game Boy Camera data 
 * (photos, checksums, etc.).
 */

#define GBCAMERA_MAX_RAM 0x2000

void gb_camera_generate_known_checksums();
bool gb_camera_download_photos();
bool gb_camera_upload_photos(const void* data, size_t size);

#endif
