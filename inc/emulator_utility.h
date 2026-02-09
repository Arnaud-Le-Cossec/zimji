#ifndef ZIMJI_EMU_H_INCLUDED
#define ZIMJI_EMU_H_INCLUDED

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define EMU_LINE_BUFFER_SIZE 80

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
size_t emu_pseudoBin_Load(char* filename, uint32_t* memory_ptr, size_t memory_size);

#endif // ZIMJI_EMU_H_INCLUDED