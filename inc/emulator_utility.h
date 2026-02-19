#ifndef ZIMJI_EMU_H_INCLUDED
#define ZIMJI_EMU_H_INCLUDED

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define EMU_LINE_BUFFER_SIZE 80

#define EMU_MEMMON_PAGESIZE_DEFAULT 64

/**
 * @brief Get number of lines
 * @param filename Dumpfile file name
 * @returns Maximum address
 */
size_t emu_pseudoBin_getSize(char* filename);

/**
 * @brief Load memory from dumpfile
 * @param filename Dumpfile file name
 * @param memory_ptr Load target
 * @param memory_size Max memory size
 * @returns Number of bytes loaded. 0 if error
 */
size_t emu_pseudoBin_load(char* filename, uint32_t* memory_ptr, size_t memory_size);

/**
 * @brief Execute memory monitor in console
 * @param memory_ptr Memory space pointer
 * @param memory_size Memory space size
 * @returns None
 */
void emu_memMonitor_cli(uint32_t* memory_ptr, size_t memory_size);

/**
 * @brief Print memory
 * @param memory_ptr Memory space pointer
 * @param memory_size Memory space size
 * @param start_addr Start address
 * @param page_size Number of memory blocks to display
 * @returns None
 */
void emu_memMonitor_page(uint32_t* memory_ptr, size_t memory_size, uint32_t start_addr, uint32_t page_size);

#endif // ZIMJI_EMU_H_INCLUDED