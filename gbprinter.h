#ifndef GBPRINTER_H
#define GBPRINTER_H

#include <stdbool.h>
#include <stddef.h>

/*
 * Interface for a hypothetical Game Boy Printer.
 * Some carts are "printer_compatible," 
 * so we can read or send data that a printer might handle.
 */

bool gb_printer_download_images();
bool gb_printer_print_data(const void* data, size_t size);

#endif
