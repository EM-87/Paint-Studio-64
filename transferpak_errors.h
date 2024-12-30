#ifndef TRANSFERPAK_ERRORS_H
#define TRANSFERPAK_ERRORS_H

/*
 * Enumerates possible Transfer Pak error states
 * for reading/writing from the N64 Transfer Pak.
 */

typedef enum {
    TPAK_ERR_NONE = 0,
    TPAK_ERR_INIT_FAIL,
    TPAK_ERR_DISCONNECTED,
    TPAK_ERR_MAX_RETRIES,
    TPAK_ERR_OUT_OF_RANGE,
    TPAK_ERR_NO_SRAM,
    TPAK_ERR_CHUNK_FAIL
} TpakError;

#endif // TRANSFERPAK_ERRORS_H
